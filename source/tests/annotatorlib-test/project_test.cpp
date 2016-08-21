
#include <gmock/gmock.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Project.h>
#include <string>

class project_test : public testing::Test {
 public:
};

TEST_F(project_test, saveProject) {
        try{
            std::string path = "test.xml";
            AnnotatorLib::Project *project = AnnotatorLib::Project::create("testname", "video", "video.mpg", "json", "test.json");
            project->setPath(path);
            project->load();
            AnnotatorLib::Session * session = project->getSession();
            AnnotatorLib::Object object(AnnotatorLib::Object::genId());
            object.setName("testobject");
            session->addObject(&object);

            AnnotatorLib::Frame frame(1);
            session->addFrame(&frame);

            AnnotatorLib::Attribute attribute(AnnotatorLib::Attribute::genId(), AnnotatorLib::AttributeType::BOOLEAN, "light");
            AnnotatorLib::AttributeValue defaultValue(false);
            attribute.setDefaultValue(&defaultValue);
            session->addAttribute(&attribute);

            AnnotatorLib::Annotation annotation(AnnotatorLib::Annotation::genId());
            annotation.addAttribute(&attribute);
            annotation.setFrame(&frame);
            annotation.setObject(&object);
            annotation.setPosition(10,10,3,3);

            session->addAnnotation(&annotation);


            AnnotatorLib::Project::save(project, path);
            delete project;
        }catch(std::exception &e){
            e.what();
        }
    }


TEST_F(project_test, loadProject) {
        try{
            AnnotatorLib::Project *project = AnnotatorLib::Project::load("test.xml");
            delete project;
        }catch(std::exception &e){
            e.what();
        }
    }

TEST_F(project_test, saveLoadProject) {
        try{
            std::string path = "testsaveload.xml";
            AnnotatorLib::Project *project = AnnotatorLib::Project::create("testname", "video", "video.mpg", "json", "test.json");
            project->setPath(path);
            project->load();
            AnnotatorLib::Session * session = project->getSession();
            AnnotatorLib::Object * object = new AnnotatorLib::Object(AnnotatorLib::Object::genId());
            session->addObject(object);


            AnnotatorLib::Project::save(project, path);

            AnnotatorLib::Project *projectLoaded = AnnotatorLib::Project::load("testsaveload.xml");

            ASSERT_EQ(projectLoaded->getName() , "testname");
            ASSERT_TRUE(project->equals(projectLoaded));

            delete project;
            delete projectLoaded;
        }catch(std::exception &e){
            e.what();
        }
    }

TEST_F(project_test, equals) {
        AnnotatorLib::Project *project = AnnotatorLib::Project::create("testname", "video", "video.mpg", "json", "test.json");
        AnnotatorLib::Project *project1 = AnnotatorLib::Project::create("testname_", "video", "video.mpg", "json", "test.json");
        AnnotatorLib::Project *project2 = AnnotatorLib::Project::create("testname", "images", "video.mpg", "json", "test.json");
        AnnotatorLib::Project *project3 = AnnotatorLib::Project::create("testname", "video", "video_.mpg", "json", "test.json");
        AnnotatorLib::Project *project4 = AnnotatorLib::Project::create("testname", "video", "video.mpg", "xml", "test.json");
        AnnotatorLib::Project *project5 = AnnotatorLib::Project::create("testname", "video", "video.mpg", "json", "test_.json");
        AnnotatorLib::Project *project6 = AnnotatorLib::Project::create("testname", "video", "video.mpg", "json", "test.json");

        ASSERT_FALSE(project->equals(project1));
        ASSERT_FALSE(project->equals(project2));
        ASSERT_FALSE(project->equals(project3));
        ASSERT_FALSE(project->equals(project4));
        ASSERT_FALSE(project->equals(project5));

        ASSERT_TRUE(project->equals(project6));

        delete project;
        delete project1;
        delete project2;
        delete project3;
        delete project4;
        delete project5;
        delete project6;
    }
