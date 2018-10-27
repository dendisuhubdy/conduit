#ifndef CONDUIT_COMPOSE_HPP
#define CONDUIT_COMPOSE_HPP

namespace conduit {

template <class X, class F>
auto evaluate(X&& x, F f) -> decltype(f(FWD(x))) {
  return f(FWD(x));
}

template <class X, class F, class... Fs>
auto evaluate(X&& x, F f, Fs&&... fs)
  -> decltype(evaluate(f(FWD(x)), FWD(fs)...)) {
  return evaluate(f(FWD(x)), FWD(fs)...);
}

template <class... Fs>
auto compose(Fs&&... fs) {
  return
    [=](auto&& x) -> decltype(evaluate(FWD(x), fs...)) {
      return evaluate(FWD(x), fs...);
    };
}

namespace operators {
template <class G, class F>
auto operator>>(G&& g, F&& f)
  -> decltype(g.begin(), f(FWD(g)).begin(), f(FWD(g))) {
  return f(FWD(g));
}

} // namespace operators
} // namespace conduit

#endif
