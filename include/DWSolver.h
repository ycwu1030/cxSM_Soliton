#ifndef DWSOLVER_H
#define DWSOLVER_H

#include "Relaxation.h"
#include "Potential.h"
#include <string>
#include <functional>

class DWSolver
{
private:
    int _N_Fields;
    int _ODE_DOF;
    int _N_Left_Bound;
    int _N_Right_Bound;
    int _mesh_points;
    VD _X;
    VVD _Y;

    Relaxation _ODESolver;
    Potential *_mod;
    VD _overall_scale;
    double _z_scale;
    double _z_range;
    double _x_half_range;
    VD _Left_Bound;
    VD _Right_Bound;
    VD _Field_Basis;
    void SetOverallScale(double overall_scale);
    
    void SetDWODE_LeftBoundary(const Relaxation_Param relax_param, VVD &S);
    void SetDWODE_RightBoundary(const Relaxation_Param relax_param, VVD &S);
    void SetDWODE_Body(const Relaxation_Param relax_param, VVD &S);
    void SetInitial();
    std::function<VD(VD)> _dV_replace;
    std::function<VVD(VD)> _d2V_replace;

public:
    DWSolver();
    DWSolver(Potential *mod, int mesh_points = 400);
    DWSolver(Potential *mod, VD Left_Bound, VD Right_Bound, int mesh_points = 400);
    ~DWSolver(){};

    void SetZRange(); // Set the z range automatically according to the potential
    void SetZRange(double z_range);
    void SetMeshPoints(int mesh_points = 400){_mesh_points = mesh_points;};
    void SetBoundary(VD Left_Bound, VD Right_Bound);
    void SetOverallScale(VD overall_scale);

    bool Solve(VD &X, VVD &Y);

    void PrintSolution();
    void DumpSolution(std::string filename);

    void SetDWODE(const Relaxation_Param relax_param, VVD &S); // Used by ODE solver, not for users
};



#endif //DWSolver_H