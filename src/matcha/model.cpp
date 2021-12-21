#include "matcha/model.h"

#include <fstream>

// model serialization
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
// #include <boost/archive/xml_iarchive.hpp>
// #include <boost/archive/xml_oarchive.hpp>
#include <boost/compute/version.hpp>

#include "matcha/backend/ndarray.h"

namespace matcha {

Model::Model(Transformer transformer, Estimator estimator)
  : transformer(transformer),
    estimator(estimator)
{
  initTensor();
}

Model::Model(Transformer transformer)
  : transformer(transformer)
{
  initTensor();
}

Model::Model(Estimator estimator)
  : estimator(estimator)
{
  initTensor();
}

Model::Model() {
  initTensor();
}

void Model::initTensor() {
  tensor = new backend::Ndarray<double>{5, 5, 5};
  AbstractTensor<double>& t = *tensor;
}

Model::~Model() {
}

void Model::train() {

}

void Model::eval() {
}

template <class OStream>
void Model::save(OStream& os) {
  boost::archive::binary_oarchive ar(os);
  ar & *this;
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
  boost::archive::binary_iarchive ar(is);
  Model buff;
  ar >> buff;
  return buff;
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
  std::cout << "serializing" << std::endl;
  ar & *tensor;
}

}