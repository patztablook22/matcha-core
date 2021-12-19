#pragma once

#include "matcha/estimators/estimator.h"
#include "matcha/transformers/transformer.h"

#include <iostream>

#include <boost/serialization/access.hpp>

namespace matcha {

class Model {
  private:
    Transformer transformer;
    Estimator estimator;

  public:
    // constructors
    Model(Transformer transformer, Estimator estimator);
    Model(Transformer transformer);
    Model(Estimator estimator);
    Model();

    // destructor
    ~Model();

    // actions
    void train();
    void eval();

    // serialization
    template <class OStream>
    void save(OStream& os);
    void save(const std::string filepath);
    void save(const char* filepath);

    template <class IStream>
    static Model load(IStream& is);
    static Model load(std::string filepath);
    static Model load(const char* filepath);
  
  private:
    friend class ::boost::serialization::access;

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version);
};

}