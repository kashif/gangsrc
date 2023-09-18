/* GANG Software
 * BASE/math/Fit.H
 * Copyright (C) 2002 Nicholas Schmitt <nick@gang.umass.edu>
 * Wed Sep 18 16:39:46 2002
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef math_Fit_INCLUDED
#define math_Fit_INCLUDED

#include "base/vector.H"
#include "Vector2Math.H"
#include "Vector3Math.H"
#include "VectorX.H"
#include "Matrix.H"

namespace math {

template<class Real>
void
best_fit_line(
  VectorX<Real,2U> &X,
  base::vector< Vector2Math<Real> > const &x )
{
  /*
    Computes best fitting line through a set of points in R^3
    Computes least-squares fit for
      y = a x + b
    Returns X = {a, b}
  */

  Matrix<Real> M;
  _best_fit_line_matrix( M, x );

  VectorX<Real,3U> Ax;
  Real Ex;
  VectorX<Real,3U> X1;
  _best_fit_line( X1, Ex, M, 1 );
  if (effectively_zero(X1[1]))
  {
    throw base::Exception("");
  }
  X[0] = -X1[0];
  X[1] = -X1[2];
  X /= X1[1];
}

template<class Real>
void
best_fit_line_2(
  VectorX<Real,3U> &a,
  base::vector< Vector2Math<Real> > const &x )
{
  /*
    Computes best fitting line through a set of points in R^3
    Computes least-squares fit for
      x = a1 y + b1
      y = a2 x + b2
    and chooses the best of the two.
    NOTE: this method is not invariant under isometries of R^3.
      but is more efficient than the symmetric solution because it is linear.
  */

  uint n = x.size();
  if (n < 3) {
    throw base::Exception("");
  }

  Matrix<Real> M;
  _best_fit_line_matrix( M, x );

  VectorX<Real,3U> Ax;
  Real Ex;
  bool Bx = false;
  try {
    _best_fit_line( Ax, Ex, M, 0 );
  }
  catch ( base::Exception const & ) {
    Bx = true;
  }

  VectorX<Real,3U> Ay;
  Real Ey;
  bool By = false;
  try {
    _best_fit_line( Ay, Ey, M, 1 );
  }
  catch ( base::Exception const & ) {
    By = true;
  }

  if (Bx && By) {
    throw base::Exception("");
  }
  else if (Bx) {
    a = Ay;
  }
  else if (By) {
    a = Ax;
  }
  else {
    // no exceptions
    if (Ex <= Ey) { a = Ax; }
    else { a = Ay; }
  }
}

template<class Real>
void
_best_fit_line_matrix(
  Matrix<Real> &M,
  base::vector< Vector2Math<Real> > const &x )
{
  uint n  = x.size();

  Real M1 = n;
  Real Mx = 0.0;
  Real My = 0.0;
  Real Mxx = 0.0;
  Real Mxy = 0.0;
  Real Myy = 0.0;

  uint i;
  for ( i = 0; i < n; i++ )
  {
    Vector2Math<Real> const &v = x[i];
    Mx += v[0];
    My += v[1];
    Mxx += sqr(v[0]);
    Mxy += v[0] * v[1];
    Myy += sqr(v[1]);
  }

  M.allocate(3U);

  M[0][0] = Mxx;
  M[0][1] = Mxy;
  M[0][2] = Mx;

  M[1][0] = Mxy;
  M[1][1] = Myy;
  M[1][2] = My;

  M[2][0] = Mx;
  M[2][1] = My;
  M[2][2] = M1;
}

template<class Real>
void
_best_fit_line(
  VectorX< Real,3U> &x,
  Real &error,
  Matrix<Real> const &M,
  uint c )
{
  /*
    Subroutine for best_fit_line() to compute best fitting line through
    a set of points.

    Input:
    M codifies the set of input points;
      M = A^t A, where A = {{x1,y1,z1,1},{x2,y2,z2,2},...}
    c = one of 0,1,2; specifies which to solve:
      x = a1 y + b1 z + c1
      y = a2 x + b2 z + c2
      z = a3 x + b3 y + c3

    Output:
    x = the line
    error = error measuer; sum of squares

    Method:
      The set of n equations z_i = a x_i + b y_i + c in matrix form is
         A X = b,
      where
         A = {{x1,y1,1},{x2,y2,1},...}
         X = {{a},{b},{c}}
         B = {{z1},{z2},...}

      Solve
        A^t (A x - B) = 0,
      by solving the linear system
        A^t A x = A^t B
      (A, B are known, x is unknown)
  */

  uint n[2];
  if (c==0) { n[0]=1; n[1]=2; }
  else if (c==1) { n[0]=0; n[1]=2; }
  else { DIE(); }

  // set up S
  Matrix<Real> S;
  S.allocate(2);
  
  uint i;
  for (i = 0; i < 2; i++ )
  {
    uint j;
    for (j = 0; j < 2; j++ )
    {
      S[i][j] = M[n[i]][n[j]];
    }
  }

  // set up T
  Vector<Real> T;
  T.allocate(2);
  for (i = 0; i < 2; i++ )
  {
    T[i] = M[n[i]][c];
  }

  // solve the system
  S.linear_solve(T);

  // put solution into x
  for (i = 0; i < 2; i++ )
  {
    x[n[i]] = T[i];
  }
  x[c] = -1.0;

  // normalize the solution x
  Real q = abs( x[0], x[1] );
  if (effectively_zero(q)) {
    throw base::Exception("");
  }
  x /= q;

  // compute error
  error = 0.0;
  for (i = 0; i < 3; i++ )
  {
    uint j;
    for (j = 0; j < 3; j++ )
    {
      error += x[i]*x[j]*M[i][j];
    }
  }
}

template<class Real>
void
best_fit_plane(
  VectorX<Real,3U> &X,
  base::vector< Vector3Math<Real> > const &x )
{
  /*
    Computes best fitting plane through a set of points in R^3
    Computes least-squares fit for
      z = a x + b y + c
    Returns X = {a, b, c}
  */

  Matrix<Real> M;
  _best_fit_plane_matrix( M, x );

  VectorX<Real,4U> Ax;
  Real Ex;
  VectorX<Real,4U> X1;
  _best_fit_plane( X1, Ex, M, 2 );
  if (effectively_zero(X1[2]))
  {
    throw base::Exception("");
  }
  X[0] = -X1[0];
  X[0] = -X1[1];
  X[0] = -X1[3];
  X /= X1[2];
}

template<class Real>
void
best_fit_plane_3(
  VectorX<Real,4U> &a,
  base::vector< Vector3Math<Real> > const &x )
{
  /*
    Computes best fitting plane through a set of points in R^3
    Computes least-squares fit for
      x = a1 y + b1 z + c1
      y = a2 x + b2 z + c2
      z = a3 x + b3 y + c3
    and chooses the best of the three.
    NOTE: this method is not invariant under isometries of R^3.
      but is more efficient than the symmetric solution because it is linear.
  */

  uint n = x.size();
  if (n < 3) {
    throw base::Exception("");
  }

  Matrix<Real> M;
  _best_fit_plane_matrix( M, x );

  VectorX<Real,4U> Ax;
  Real Ex;
  bool Bx = false;
  try {
    _best_fit_plane( Ax, Ex, M, 0 );
  }
  catch ( base::Exception const & ) {
    Bx = true;
  }

  VectorX<Real,4U> Ay;
  Real Ey;
  bool By = false;
  try {
    _best_fit_plane( Ay, Ey, M, 1 );
  }
  catch ( base::Exception const & ) {
    By = true;
  }

  VectorX<Real,4U> Az;
  Real Ez;
  bool Bz = false;
  try {
    _best_fit_plane( Az, Ez, M, 2 );
  }
  catch ( base::Exception const & ) {
    Bz = true;
  }

  if (Bx && By && Bz) {
    throw base::Exception("");
  }
  else if (Bx && By) {
    a = Az;
  }
  else if (Bx && Bz) {
    a = Ay;
  }
  else if (By && Bz) {
    a = Ax;
  }
  else if (Bx) {
    a = ( Ey <= Ez ? Ay : Az );
  }
  else if (By) {
    a = ( Ex <= Ez ? Ax : Az );
  }
  else if (Bz) {
    a = ( Ex <= Ey ? Ax : Ay );
  }
  else {
    // no exceptions
    if (Ex <= Ey) {
      if (Ex <= Ez) { a = Ax; }
      else { a = Az; }
    }
    else {
      if (Ey <= Ez) { a = Ay; }
      else { a = Az; }
    }
  }
}

template<class Real>
void
_best_fit_plane_matrix(
  Matrix<Real> &M,
  base::vector< Vector3Math<Real> > const &x )
{
  uint n  = x.size();

  Real M1 = n;
  Real Mx = 0.0;
  Real My = 0.0;
  Real Mz = 0.0;
  Real Mxx = 0.0;
  Real Mxy = 0.0;
  Real Mxz = 0.0;
  Real Myy = 0.0;
  Real Myz = 0.0;
  Real Mzz = 0.0;

  uint i;
  for ( i = 0; i < n; i++ )
  {
    Vector3Math<Real> const &v = x[i];
    Mx += v[0];
    My += v[1];
    Mz += v[2];
    Mxx += sqr(v[0]);
    Mxy += v[0] * v[1];
    Mxz += v[0] * v[2];
    Myy += sqr(v[1]);
    Myz += v[1] * v[2];
    Mzz += sqr(v[2]);
  }

  M.allocate(4U);

  M[0][0] = Mxx;
  M[0][1] = Mxy;
  M[0][2] = Mxz;
  M[0][3] = Mx;

  M[1][0] = Mxy;
  M[1][1] = Myy;
  M[1][2] = Myz;
  M[1][3] = My;

  M[2][0] = Mxz;
  M[2][1] = Myz;
  M[2][2] = Mzz;
  M[2][3] = Mz;

  M[3][0] = Mx;
  M[3][1] = My;
  M[3][2] = Mz;
  M[3][3] = M1;
}

template<class Real>
void
_best_fit_plane(
  VectorX< Real,4U> &x,
  Real &error,
  Matrix<Real> const &M,
  uint c )
{
  /*
    Subroutine for best_fit_plane() to compute best fitting plane through
    a set of points.

    Input:
    M codifies the set of input points;
      M = A^t A, where A = {{x1,y1,z1,1},{x2,y2,z2,2},...}
    c = one of 0,1,2; specifies which to solve:
      x = a1 y + b1 z + c1
      y = a2 x + b2 z + c2
      z = a3 x + b3 y + c3

    Output:
    x = the plane
    error = error measuer; sum of squares

    Method:
      The set of n equations z_i = a x_i + b y_i + c in matrix form is
         A X = b,
      where
         A = {{x1,y1,1},{x2,y2,1},...}
         X = {{a},{b},{c}}
         B = {{z1},{z2},...}

      Solve
        A^t (A x - B) = 0,
      by solving the linear system
        A^t A x = A^t B
      (A, B are known, x is unknown)
  */

  uint n[3];
  if (c==0) { n[0]=1; n[1]=2; n[2]=3; }
  else if (c==1) { n[0]=0; n[1]=2; n[2]=3; }
  else if (c==2) { n[0]=0; n[1]=1; n[2]=3; }
  else { DIE(); }

  // set up S
  Matrix<Real> S;
  S.allocate(3);
  
  uint i;
  for (i = 0; i < 3; i++ )
  {
    uint j;
    for (j = 0; j < 3; j++ )
    {
      S[i][j] = M[n[i]][n[j]];
    }
  }

  // set up T
  Vector<Real> T;
  T.allocate(3);
  for (i = 0; i < 3; i++ )
  {
    T[i] = M[n[i]][c];
  }

  // solve the system
  S.linear_solve(T);

  // put solution into x
  for (i = 0; i < 3; i++ )
  {
    x[n[i]] = T[i];
  }
  x[c] = -1.0;

  // normalize the solution x
  Real q = abs( x[0], x[1], x[2] );
  if (effectively_zero(q)) {
    throw base::Exception("");
  }
  x /= q;

  // compute error
  error = 0.0;
  for (i = 0; i < 4; i++ )
  {
    uint j;
    for (j = 0; j < 4; j++ )
    {
      error += x[i]*x[j]*M[i][j];
    }
  }
}

} // namespace math

#endif // math_Fit_INCLUDED
