#include <modlm/dist-uniform.h>
#include <modlm/macros.h>

using namespace modlm;

DistUniform::DistUniform(const std::string & sig) : DistBase(sig) {
  if(sig != "uniform")
    THROW_ERROR("Bad signature: " << sig);
}

void DistUniform::calc_word_dists(const Sentence & ctxt,
                             const Sentence & wids,
                             float uniform_prob,
                             bool leave_one_out,
                             std::vector<TrainingTarget> & trgs,
                             int & dense_offset,
                             int & sparse_offset) const {
  for(size_t i = 0; i < wids.size(); i++) 
    trgs[i].first[dense_offset] = uniform_prob;
  dense_offset++;
}
