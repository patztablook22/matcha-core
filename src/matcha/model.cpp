#include "matcha/model.h"

#include <fstream>

// model serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/compute/version.hpp>

namespace matcha {

Model::Model(Transformer transformer, Estimator estimator)
  : transformer(transformer),
    estimator(estimator)
{}

Model::Model(Transformer transformer)
  : transformer(transformer)
{}

Model::Model(Estimator estimator)
  : estimator(estimator)
{}

Model::Model() {
}

Model::~Model() {
}

void Model::train() {

}

void Model::eval() {
}

template <class OStream>
void Model::save(OStream& os) {
  boost::archive::text_oarchive ar(os);
  ar << *this;
}

void Model::save(const std::string filepath) {
  std::ofstream ofs(filepath);
  save(ofs);
}

void Model::save(const char* filepath) {
  save(std::string(filepath));
}

template <class IStream>
Model Model::load(IStream& is) {
  boost::archive::text_iarchive ar(is);
  return Model();
}

Model Model::load(std::string filepath) {
  std::ifstream ifs(filepath);
  return load(ifs);
}

Model Model::load(const char* filepath) {
  return load(std::string(filepath));
}

template <class Archive>
void Model::serialize(Archive& ar, const unsigned int version) {
}

}