// Copyright 2016-2017 Annotator Team

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Attribute.h>
#include <AnnotatorLib/Commands/UpdateAttribute.h>
#include <AnnotatorLib/Session.h>
#include <exception>

AnnotatorLib::Commands::UpdateAttribute::UpdateAttribute(
    shared_ptr<AnnotatorLib::Annotation> annotation, std::string name,
    std::string value)
    : annotation(annotation), name(name), value(value) {}

bool AnnotatorLib::Commands::UpdateAttribute::execute(
    AnnotatorLib::Session *informSession) {
  std::shared_ptr<Attribute> attribute =
      annotation->getAttributeWithoutDefaults(name);
  if (!attribute) {
    this->wasDefault = true;
    shared_ptr<Attribute> attribute_ = annotation->getAttribute(name);
    attribute = std::make_shared<Attribute>(attribute_);
    assert(attribute);
    annotation->addAttribute(attribute);
  }
  oldValue = attribute->getValue();
  std::shared_ptr<AnnotatorLib::AttributeValue> av =
      AnnotatorLib::Attribute::createAttributeValue(oldValue->getType(), value);
  attribute->setValue(av);

  if (informSession) {
    informSession->updateAnnotation(annotation);
    informSession->updateAttribute(attribute);
  }
  return true;
}

bool AnnotatorLib::Commands::UpdateAttribute::undo(
    AnnotatorLib::Session *informSession) {
  // TODO
	return true;
}
