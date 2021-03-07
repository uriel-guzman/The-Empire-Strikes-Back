struct Item {
  int w, cost;
};

for (auto &cur : items)
  fore (w, W + 1, cur.w) // [cur.w, W]
    umax(dp[w], dp[w - cur.w] + cur.cost);