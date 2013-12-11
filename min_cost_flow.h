#ifndef MIN_COST_FLOW_H
#define MIN_COST_FLOW_H

#include "graph.h"

#include <boost/tuple/tuple.hpp>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include <queue>

using namespace std;

DECLARE_int32(alpha_scaling_factor);

class MinCostFlow {

 public:
 MinCostFlow(Graph graph): graph_(graph) {
  }

  void cycleCancelling();
  void successiveShortestPath();
  void successiveShortestPathPotentials();
  void costScaling();
  void BellmanFord(const vector<uint32_t>& source_node,
                   vector<int32_t>& distance, vector<uint32_t>& predecessor);
  void DijkstraSimple(const vector<uint32_t>& source_node,
                      vector<int32_t>& distance, vector<uint32_t>& predecessor);
  void DijkstraOptimized(const vector<uint32_t>& source_node,
                         vector<int32_t>& distance,
                         vector<uint32_t>& predecessor);
  void logCosts(const vector<int32_t>& distance,
                const vector<uint32_t>& predecessor);

 private:
  Graph graph_;
  uint32_t relabel_cnt;
  uint32_t pushes_cnt;

  // Returns true if it removes a negative cycle.
  bool removeNegativeCycles(vector<int32_t>& distance,
                            vector<uint32_t>& predecessor);
  void augmentFlow(vector<int32_t>& distance, vector<uint32_t>& predecessor,
                   uint32_t src_node, uint32_t dst_node);
  void maxFlow();
  void reduceCost(vector<int32_t>& potential);
  void refine(vector<int32_t>& potential, int32_t eps);
  void discharge(queue<uint32_t>& active_nodes, vector<int32_t>& potential,
                 vector<int32_t>& nodes_demand, int32_t eps);
  int32_t scaleUpCosts();
  void globalPotentialsUpdate(vector<int32_t>& potential, int32_t eps);
  bool priceRefinement(vector<int32_t>& potential, int32_t eps);
  void arcsFixing(vector<int32_t>& potential, int32_t fix_threshold);
  void arcsUnfixing(vector<int32_t>& potential, int32_t fix_threshold);
  void pushLookahead(uint32_t src_node_id, uint32_t dst_node_id);

};
#endif
