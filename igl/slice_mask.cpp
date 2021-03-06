#include "slice_mask.h"
#include <cassert>

template <typename DerivedX>
IGL_INLINE void igl::slice_mask(
  const Eigen::PlainObjectBase<DerivedX> & X,
  const Eigen::Array<bool,Eigen::Dynamic,1> & R,
  const Eigen::Array<bool,Eigen::Dynamic,1> & C,
  Eigen::PlainObjectBase<DerivedX> & Y)
{
  int xm = X.rows();
  int xn = X.cols();
  int ym = R.count();
  int yn = C.count();
  assert(R.size() == X.rows() && "R.size() should match X.rows()");
  assert(C.size() == X.cols() && "C.size() should match X.cols()");
  Y.resize(ym,yn);
  {
    int yi = 0;
    for(int i = 0;i<xm;i++)
    {
      if(R(i))
      {
        int yj = 0;
        for(int j = 0;j<xn;j++)
        {
          if(C(j))
          {
            Y(yi,yj) = X(i,j);
            yj++;
          }
        }
        yi++;
      }
    }
  }
}

template <typename DerivedX>
IGL_INLINE void igl::slice_mask(
  const Eigen::PlainObjectBase<DerivedX> & X,
  const Eigen::Array<bool,Eigen::Dynamic,1> & R,
  const int dim,
  Eigen::PlainObjectBase<DerivedX> & Y)
{
  switch(dim)
  {
    case 1:
    {
      const int ym = R.count();
      Y.resize(ym,X.cols());
      assert(X.rows() == R.size() && "X.rows() should match R.size()");
      {
        int yi = 0;
        for(int i = 0;i<X.rows();i++)
        {
          if(R(i))
          {
            Y.row(yi++) = X.row(i);
          }
        }
      }
      return;
    }
    case 2:
    {
      const auto & C = R;
      const int yn = C.count();
      Y.resize(X.rows(),yn);
      assert(X.cols() == R.size() && "X.cols() should match R.size()");
      {
        int yj = 0;
        for(int j = 0;j<X.cols();j++)
        {
          if(C(j))
          {
            Y.col(yj++) = X.col(j);
          }
        }
      }
      return;
    }
    default:
      assert(false && "Unsupported dimension");
      return;
  }
}

template <typename DerivedX>
IGL_INLINE Eigen::PlainObjectBase<DerivedX> igl::slice_mask(
  const Eigen::PlainObjectBase<DerivedX> & X,
  const Eigen::Array<bool,Eigen::Dynamic,1> & R,
  const Eigen::Array<bool,Eigen::Dynamic,1> & C)
{
  Eigen::PlainObjectBase<DerivedX> Y;
  igl::slice_mask(X,R,C,Y);
  return Y;
}

template <typename DerivedX>
IGL_INLINE Eigen::PlainObjectBase<DerivedX> igl::slice_mask(
  const Eigen::PlainObjectBase<DerivedX>& X,
  const Eigen::Array<bool,Eigen::Dynamic,1> & R,
  const int dim)
{
  Eigen::PlainObjectBase<DerivedX> Y;
  igl::slice_mask(X,R,dim,Y);
  return Y;
}

#ifdef IGL_STATIC_LIBRARY
template void igl::slice_mask<Eigen::Matrix<int, -1, -1, 0, -1, -1> >(Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::Array<bool, -1, 1, 0, -1, 1> const&, int, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&);
#endif
