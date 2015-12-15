#pragma once

#include <iostream>
#include <string>
#include <modlm/sentence.h>

namespace modlm {

// A base class implementing the functions necessary for calculation
class DistBase {

public:

  DistBase(const std::string & sig) : ctxt_len_(0) { }
  virtual ~DistBase() { }

  // Get the signature of this class that uniquely identifies it for loading
  // at test time. In other words, the signature can collapse any information
  // only needed at training time.
  virtual std::string get_sig() const = 0;

  // Add stats from one sentence at training time for count-based models
  virtual void add_stats(const Sentence & sent) = 0;

  // Perform any final calculations on the stats
  virtual void finalize_stats() { }

  // Get the length of n-gram context that this model expects
  virtual size_t get_ctxt_len() const { return ctxt_len_; }

  // Get the number of contextual features we can expect from this model
  virtual size_t get_ctxt_size() const = 0;
  // And calculate these features. held_out_wid is a word id to hold out from
  // feature calculation when leaving one out
  virtual void calc_ctxt_feats(const Sentence & ctxt,
                               WordId held_out_wid,
                               float* feats_out) const = 0;

  // Get the number of distributions we can expect from this model
  virtual size_t get_dist_size() const = 0;
  // And calculate these features given context, for words wids. uniform_prob
  // is the probability assigned in unknown contexts. leave_one_out indicates
  // whether we should subtract one from the counts for cross-validation.
  // prob_out is the output.
  virtual void calc_word_dists(const Sentence & ctxt,
                               const Sentence & wids,
                               float uniform_prob,
                               bool leave_one_out,
                               float* prob_out) const = 0;

  // Read/write model. If dict is null, use numerical ids, otherwise strings.
  virtual void write(DictPtr dict, std::ostream & str) const = 0;
  virtual void read(DictPtr dict, std::istream & str) const = 0;

protected:
  size_t ctxt_len_;  

};

typedef std::shared_ptr<DistBase> DistPtr;

}
