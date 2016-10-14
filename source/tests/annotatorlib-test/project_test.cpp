
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Project.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

using namespace AnnotatorLib;
using std::shared_ptr;

class project_test : public testing::Test {
 public:
};

TEST_F(project_test, saveProject) {
  try {
    std::string path = "test.xml";
    std::shared_ptr<AnnotatorLib::Project> project =
        Project::create("testname", "video", "video.mpg", "json", "test.json");
    project->setPath(path);
    project->load();
    std::shared_ptr<Session> session = project->getSession();
    shared_ptr<Object> object = std::make_shared<Object>();
    object->setName("testobject");
    session->addObject(shared_ptr<Object>(object));

    shared_ptr<Frame> frame = std::make_shared<Frame>(1);
    session->addFrame(shared_ptr<Frame>(frame));

    shared_ptr<Attribute> attribute = std::make_shared<Attribute>(
        Attribute::genId(), AttributeType::BOOLEAN, "light");
    AttributeValue defaultValue(false);
    attribute->setDefaultValue(&defaultValue);
    session->addAttribute(shared_ptr<Attribute>(attribute));

    shared_ptr<Annotation> annotation =
        Annotation::make_shared(frame, object, AnnotationType::RECTANGLE);
    annotation->addAttribute(attribute);
    annotation->setPosition(10, 10, 3, 3);

    session->addAnnotation(shared_ptr<Annotation>(annotation));

    Project::save(project, path);
  } catch (std::exception &e) {
    e.what();
  }
}

TEST_F(project_test, loadProject) {
  try {
    Project::load("test.xml");
  } catch (std::exception &e) {
    e.what();
  }
}

TEST_F(project_test, saveLoadProject) {
  try {
    std::string path = "testsaveload.xml";
    std::shared_ptr<AnnotatorLib::Project> project =
        Project::create("testname", "video", "video.mpg", "json", "test.json");
    project->setPath(path);
    project->load();
    std::shared_ptr<AnnotatorLib::Session> session = project->getSession();
    session->addObject(shared_ptr<Object>(std::make_shared<Object>()));

    Project::save(project, path);

    std::shared_ptr<AnnotatorLib::Project> projectLoaded =
        Project::load("testsaveload.xml");

    ASSERT_EQ(projectLoaded->getName(), "testname");
    ASSERT_TRUE(project->equals(projectLoaded));

  } catch (std::exception &e) {
    e.what();
  }
}

TEST_F(project_test, equals) {
  std::shared_ptr<AnnotatorLib::Project> project =
      Project::create("testname", "video", "video.mpg", "json", "test.json");
  std::shared_ptr<AnnotatorLib::Project> project1 =
      Project::create("testname_", "video", "video.mpg", "json", "test.json");
  std::shared_ptr<AnnotatorLib::Project> project2 =
      Project::create("testname", "images", "video.mpg", "json", "test.json");
  std::shared_ptr<AnnotatorLib::Project> project3 =
      Project::create("testname", "video", "video_.mpg", "json", "test.json");
  std::shared_ptr<AnnotatorLib::Project> project4 =
      Project::create("testname", "video", "video.mpg", "xml", "test.json");
  std::shared_ptr<AnnotatorLib::Project> project5 =
      Project::create("testname", "video", "video.mpg", "json", "test_.json");
  std::shared_ptr<AnnotatorLib::Project> project6 =
      Project::create("testname", "video", "video.mpg", "json", "test.json");

  ASSERT_FALSE(project->equals(project1));
  ASSERT_FALSE(project->equals(project2));
  ASSERT_FALSE(project->equals(project3));
  ASSERT_FALSE(project->equals(project4));
  ASSERT_FALSE(project->equals(project5));

  ASSERT_TRUE(project->equals(project6));
}
