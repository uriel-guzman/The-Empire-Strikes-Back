struct Item {
  int w, cost;
};

for (auto& cur : items)
  for (int w = W; w >= cur.w; w--)
    umax(dp[w], dp[w - cur.w] + cur.cost);