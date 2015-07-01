#ifndef GAUSSIAN_MIXTURE_H
#define GAUSSIAN_MIXTURE_H

// Author : Benjamin Lefaudeux (blefaudeux@github)


#include "eigen_tools.h"
#include <list>
#include <algorithm>

using namespace std;
using namespace Eigen;

/*!
 * \brief Stupid index structure to help sort gaussian mixtures
 */
struct index_w {
    float weight;
    int   index;
};

/*!
 * \brief The gaussian_model struct for 3D targets & measurements -> 6D dimension
 */
struct GaussianModel {
  Matrix<float, 6,1, DontAlign> mean;
  Matrix<float, 6,6, DontAlign> cov;

  float weight;

  void reset();
};

/*!
 * \brief The gaussian_mixture is a sum of gaussian models,
 *  with according weights. Everything is public, no need to get/set...
 */
class GaussianMixture {
  public :
    GaussianMixture();

    GaussianMixture(const GaussianMixture &source);

    GaussianMixture operator=(const GaussianMixture &source);

    GaussianModel mergeGaussians(vector<int> &i_gaussians_to_merge,
                                 bool b_remove_from_mixture);


    void  normalize(float linear_offset);

    void  normalize(float linear_offset,
                    int   start_pos,
                    int   stop_pos,
                    int   step);

    void print();

    GaussianMixture  prune(float  trunc_threshold,
                           float  merge_threshold,
                           int    max_gaussians);

    void qsort();

    void selectCloseGaussians(int         i_ref,
                              float       threshold,
                              vector<int> &close_gaussians);

    int selectBestGaussian();

    void changeReferential(const Matrix4f *tranform);

 public:
    vector <GaussianModel> m_gaussians;

};

#endif // GAUSSIAN_MIXTURE_H