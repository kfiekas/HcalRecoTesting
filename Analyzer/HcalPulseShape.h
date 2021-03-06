#ifndef HcalPulseShape_h
#define HcalPulseShape_h

#include<vector>

class HcalPulseShape {
public:
  HcalPulseShape();
  void setNBin(int n);
  void setShapeBin(int i, float f);
  float getTpeak() const { return tpeak_; }
  float operator()(double time) const;
  float at(double time) const;
  float integrate(double tmin, double tmax) const;
  int nbins() const {return nbin_;}
private:
  std::vector<float> shape_;
  int nbin_;
  float tpeak_;
};

#endif
