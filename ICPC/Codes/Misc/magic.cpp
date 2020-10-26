template <class... Args>
auto magic(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1) 
    return vector(n, args...);
  else
    return vector(n, magic(args...));
}
