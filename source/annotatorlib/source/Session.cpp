// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Session_BODY

/************************************************************
 Session class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Session.h"
#include <algorithm>

namespace AnnotatorLib {

Session::Session() {}

Session::~Session() { clearAll(); }

void Session::clearData() {
  // clear data
  this->objects.clear();
  this->frames.clear();
  this->annotations.clear();
  this->classes.clear();
  this->attributes.clear();
}

void Session::clearAll() {
  // clear all
  clearData();
  this->commands.clear();
  commandIndex = 0;
}

template <typename K, typename T>
std::shared_ptr<T> find_smart_pointer(std::map<K, std::shared_ptr<T>> map,
                                      K key) {
  auto got = map.find(key);
  if (got != map.end()) {
    return got->second;
  }
  return shared_ptr<T>(nullptr);
}

template <typename K, typename T>
T* find_raw_pointer(std::unordered_map<K, std::shared_ptr<T>> map, K key) {
  return find_smart_pointer<K, T>(map, key).get();
}

bool Session::addAttribute(const shared_ptr<Attribute> attribute) {
  if (attribute) return false;
  return attributes
      .insert(std::make_pair(attribute->getId(), std::move(attribute)))
      .second;
}

shared_ptr<Attribute> Session::removeAttribute(Attribute* attribute) {
  std::shared_ptr<Attribute> got = find_smart_pointer<unsigned long, Attribute>(
      attributes, attribute->getId());
  if (got) {
    attributes.erase(attribute->getId());
  }
  return got;
}

shared_ptr<Attribute> Session::getAttribute(unsigned long id) const {
  return find_smart_pointer<unsigned long, Attribute>(attributes, id);
}

bool Session::addAnnotation(shared_ptr<Annotation> annotation,
                            bool add_associated_objects) {
  if (annotation.get() == nullptr) return false;
  auto result = annotations.insert(
      std::make_pair(annotation->getId(), std::move(annotation)));
  if (result.second) {
    Annotation::registerAnnotation(result.first->second);
    if (add_associated_objects) {
      addObject(shared_ptr<Object>(result.first->second->getObject()), false);
      addFrame(shared_ptr<Frame>(result.first->second->getFrame()), false);
    }
  }
  return result.second;
}

shared_ptr<Annotation> Session::removeAnnotation(unsigned long id,
                                                 bool unregister) {
  shared_ptr<Annotation> got =
      find_smart_pointer<unsigned long, Annotation>(annotations, id);
  if (got) {
    if (unregister) Annotation::unregisterAnnotation(got);
    annotations.erase(id);
  }
  return got;
}

shared_ptr<Annotation> Session::getAnnotation(unsigned long id) const {
  return find_smart_pointer<unsigned long, Annotation>(annotations, id);
}

shared_ptr<Annotation> Session::getAnnotation(
    const shared_ptr<Frame> frame, const shared_ptr<Object> obj) const {
  return getAnnotation(Annotation::genId(frame, obj));
}

bool Session::addClass(shared_ptr<Class> c) {
  if (c.get() == nullptr) return false;
  std::string key = c->getName();
  return classes.insert(std::make_pair(key, std::move(c))).second;
}

shared_ptr<Class> Session::removeClass(Class* c) {
  if (c == nullptr) return shared_ptr<Class>(nullptr);
  shared_ptr<Class> got =
      find_smart_pointer<std::string, Class>(classes, c->getName());
  if (got) {
    classes.erase(c->getName());
  }
  return got;
}

shared_ptr<Class> Session::getClass(std::string name) const {
  return find_smart_pointer<std::string, Class>(classes, name);
}

shared_ptr<Class> Session::getClass(unsigned long id) const {
  for (auto& pair : classes) {
    if (pair.second->getId() == id) return pair.second;
  }
  return shared_ptr<Class>(nullptr);
}

FrameMap Session::getFramesRange(unsigned long first, unsigned long last) {
  FrameMap ret_frames;
  for (auto& pair : frames) {
    if (pair.first >= first && pair.first <= last) {
      ret_frames.insert(pair);
    }
  }
  return ret_frames;
}

bool Session::addFrame(shared_ptr<Frame> frame, bool add_associated_objects) {
  if (frame.get() == nullptr) return false;
  auto result = frames.insert(std::make_pair(frame->getId(), frame));
  if (result.second && add_associated_objects &&
      result.first->second->hasAnnotations()) {
    // will add all annotations
    for (std::pair<unsigned long, weak_ptr<Annotation>> pair :
         frame->getAnnotations()) {
      addAnnotation(shared_ptr<Annotation>(pair.second), false);
    }
  }
  return result.second;
}

shared_ptr<Frame> Session::removeFrame(unsigned long frame_nmb,
                                       bool remove_annotations) {
  shared_ptr<Frame> got =
      find_smart_pointer<unsigned long, Frame>(frames, frame_nmb);
  if (got) {
    frames.erase(frame_nmb);
    if (remove_annotations) {
      for (std::pair<unsigned long, weak_ptr<Annotation>> pair :
           got->getAnnotations()) {
        removeAnnotation(pair.second.lock()->getId(), false);
      }
    }
  }
  return got;
}

shared_ptr<Frame> Session::getFrame(unsigned long number) {
  return find_smart_pointer<unsigned long, Frame>(frames, number);
  //  if (got) return got;
  //  shared_ptr<Frame> f = std::make_shared<Frame>(number);
  //  addFrame(f);  //is this really a good idea?
  //  return f;
}

bool Session::addObject(shared_ptr<Object> object,
                        bool add_associated_objects) {
  if (!object) return false;
  auto result =
      objects.insert(std::make_pair(object->getId(), std::move(object)));
  if (result.second && add_associated_objects &&
      result.first->second->hasAnnotations()) {
    // will add all annotations
    for (auto& pair : result.first->second->getAnnotations()) {
      addAnnotation(pair.second.lock(), false);
    }
  }
  if (result.second && add_associated_objects &&
      result.first->second->getClass())
    addClass(shared_ptr<Class>(result.first->second->getClass()));
  return result.second;
}

shared_ptr<Object> Session::removeObject(unsigned long id,
                                         bool remove_annotations) {
  shared_ptr<Object> got =
      find_smart_pointer<unsigned long, Object>(objects, id);
  if (got) {
    if (remove_annotations) {
      for (auto& pair : got->getAnnotations()) {
        removeAnnotation(pair.second.lock()->getId(),
                         false);  // will remove annotations
      }
    }
    objects.erase(id);
  }
  return got;
}

shared_ptr<Object> Session::getObject(unsigned long id) const {
  return find_smart_pointer<unsigned long, Object>(objects, id);
}

shared_ptr<Commands::Command> Session::execute(
    shared_ptr<Commands::Command> command) {
  std::lock_guard<std::mutex> guard(mtx);
  if (!command) return shared_ptr<AnnotatorLib::Commands::Command>(nullptr);
  commands.erase(commands.begin() + commandIndex, commands.end());
  commands.push_back(std::move(command));
  commandIndex++;
  bool success =
      commands[commandIndex - 1]->execute(this);  // execute new command
  if (success) return commands[commandIndex - 1];
  return shared_ptr<AnnotatorLib::Commands::Command>(nullptr);
}

shared_ptr<Commands::Command> Session::redo() {
  if (commands.size() > commandIndex) {
    shared_ptr<AnnotatorLib::Commands::Command> command =
        commands.at(commandIndex);
    commandIndex++;
    bool success = command->execute(this);
    if (success) return command;
  }
  return shared_ptr<AnnotatorLib::Commands::Command>(nullptr);
}

shared_ptr<Commands::Command> Session::undo() {
  if (commandIndex > 0) {
    commandIndex--;
    shared_ptr<AnnotatorLib::Commands::Command> command =
        commands.at(commandIndex);
    bool success = command->undo(this);
    if (success) return command;
  }
  return shared_ptr<AnnotatorLib::Commands::Command>(nullptr);
}

// static attributes (if any)

}  // of namespace AnnotatorLib

/************************************************************
 End of Session class body
 ************************************************************/
