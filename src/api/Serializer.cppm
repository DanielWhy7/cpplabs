export module api:Serializer;

import std;
import UValue;

export struct Serializer
{
  virtual ~Serializer() = default;
  virtual std::string serialize(const UValue &value) const = 0;
};
