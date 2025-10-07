#pragma once

#include <cmath>
#include <cstdint>
#include <vector>

using namespace std;
using ld = long double;

class Grid {
 public:
  enum class GridType { regular, adaptive };

  pair<ld, ld> bounds;
  GridType grid_type;
  uint32_t segments_num;
  ld coarsening;
  vector<ld> h;
  vector<ld> x;

  Grid(pair<ld, ld> bounds, GridType grid_type, uint32_t segments_num = 1,
       ld coarsening = 1)
      : h(), x() {
    this->bounds = bounds;
    this->grid_type = grid_type;
    this->segments_num = segments_num;
    this->coarsening = coarsening;
    if (grid_type == GridType::regular) {
      h.resize(segments_num);
      x.resize(segments_num + 1);
      ld value = (bounds.first),
         step = (bounds.second - bounds.first) / segments_num;
      for (uint32_t i = 0; i < segments_num; i++) {
        h[i] = step;
        x[i] = value;
        value += step;
      }
      x[segments_num] = bounds.second;
    } else {
      h.resize(segments_num);
      x.resize(segments_num + 1);
      ld h0 = (bounds.second - bounds.first) * (1 - coarsening) /
              (1 - pow(coarsening, segments_num));
      ld value = bounds.first;
      for (uint32_t i = 0; i < segments_num; i++) {
        h[i] = h0 * pow(coarsening, i);
        x[i] = value;
        value += h[i];
      }
      x[segments_num] = bounds.second;
    }
  }

  Grid(const Grid& grid)
      : Grid(grid.bounds, grid.grid_type, grid.segments_num, grid.coarsening) {
    for (uint32_t i = 0; i < segments_num; i++) {
      h[i] = grid.h[i];
      x[i] = grid.x[i];
    }
    x[segments_num] = grid.x[segments_num];
  }

  // returnes -1 if value is out of range
  int32_t idx(ld value) {
    for (uint32_t i = 1; i < segments_num; i++)
      if (value <= x[i]) return i - 1;
    return (value <= x[segments_num]) ? segments_num - 1 : -1;
  }

  ~Grid() {}
};