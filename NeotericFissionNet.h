#ifndef _NEOTERIC_FISSION_NET_H_
#define _NEOTERIC_FISSION_NET_H_
#include <unordered_map>
#include "OptNeotericFission.h"

namespace NeotericFission {
  constexpr int nStatisticalFeatures(5), nLayer1(128), nLayer2(64), nMiniBatch(64), nEpoch(2), nPool(1'000'000);
  constexpr double lRate(0.01), mRate(0.9), rRate(0.999), leak(0.1);

  class Net {
    Opt &opt;
    double mCorrector, rCorrector;
    std::unordered_map<int, int> tileMap;
    int nFeatures;

    // Data Pool
    xt::xtensor<double, 2> batchInput;
    xt::xtensor<double, 1> batchTarget;
    std::vector<std::pair<xt::xtensor<double, 1>, double>> pool;
    int trajectoryLength, writePos;

    xt::xtensor<double, 2> wLayer1, mwLayer1, rwLayer1;
    xt::xtensor<double, 1> bLayer1, mbLayer1, rbLayer1;
    xt::xtensor<double, 2> wLayer2, mwLayer2, rwLayer2;
    xt::xtensor<double, 1> bLayer2, mbLayer2, rbLayer2;
    xt::xtensor<double, 1> wOutput, mwOutput, rwOutput;
    double bOutput, mbOutput, rbOutput;

    xt::xtensor<double, 1> extractFeatures(const Sample &sample);
  public:
    Net(Opt &opt);
    double infer(const Sample &sample);
    void newTrajectory() { trajectoryLength = 0; }
    void appendTrajectory(const Sample &sample);
    void finishTrajectory(double target);
    int getTrajectoryLength() const { return trajectoryLength; }
    double train();
  };
}

#endif
