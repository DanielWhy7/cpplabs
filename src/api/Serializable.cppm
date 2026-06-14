export module api:Serializable;

import std;
import UValue;

export struct Serializable
{
  virtual ~Serializable() = default;
  virtual UValue to_value() const = 0;
};
