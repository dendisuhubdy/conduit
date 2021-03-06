#ifndef CONDUIT_DROP_HPP
#define CONDUIT_DROP_HPP

#include <conduit/meta.hpp>
#include <conduit/seq.hpp>

namespace conduit {
namespace F {
template<class Xs>
auto drop(Xs xs, unsigned n) -> seq<decltype(first(xs))> {
  for (auto x: xs) {
    if (n) {
      --n;
      continue;
    }
    co_yield x;
  }
};
}

auto drop = [](unsigned n) {
  return [n](auto&& xs) { 
    return F::drop(FWD(xs), n); 
  };
};

} // namespace conduit

#endif
