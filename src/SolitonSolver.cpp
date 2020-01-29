/*
 * @Description  : 
 * @Author       : Yongcheng Wu
 * @Date         : 2020-01-28 12:46:03
 * @LastEditors  : Yongcheng Wu
 * @LastEditTime : 2020-01-29 17:59:33
 */
#include <iostream>
#include <cmath>
#include "SolitonSolver.h"

using namespace std;
void SolitonSolver::SetDimension(int NFieldDim)
{
    _NFieldDim = NFieldDim;
}
void SolitonSolver::SetGridPoints(int NGrid, int MAXROUNDS)
{
    _NGrid = NGrid;
    _NPoint = _NGrid+1;
    _MAXROUNDS = MAXROUNDS;
}
void SolitonSolver::SetPotentials(ScalarFunction potential, dScalarFunction dpotential)
{
    _potential = potential;
    _dpotential = dpotential;
}
void SolitonSolver::SetParam(void *param)
{
    _param = param;
}
void SolitonSolver::SetBoundary(VD left, VD right)
{
    _bound_left = left;
    _bound_right = right;
}
void SolitonSolver::SetScale(double scaling)
{
    _Scaling = scaling;
}
void SolitonSolver::SetV0Global(double V0global)
{
    _V0_global = V0global;
}
SolitonSolver::SolitonSolver(int NFieldDim, int NGrid, int MAXROUNDS)
{
    SetDimension(NFieldDim);
    SetGridPoints(NGrid,MAXROUNDS);
    SetScale();
}
double SolitonSolver::_Calc_EnergyDensity(VD point_beg, VD point_end)
{
    double density = 0;
    density += pow(_Scaling,4)*(point_end-point_beg)*(point_end-point_beg)/pow(_DeltaZ,2)/2;
    density += _potential((point_beg+point_end)/2*_Scaling,_param);
    return density - _V0_global;
}
void SolitonSolver::_Initiative()
{
    _GridPositions_NoDim.clear();
    _FieldValue_NoDim_Current.clear();
    _FieldValue_NoDim_Last.clear();
    _EnergyDensity.clear();
    _TotalEnergy_Last = 0;
    _TotalEnergy_Current = 0;
    _DeltaZ = (_RIGHT - _LEFT)/_NGrid;
    _DeltaT = _del_t*pow(_DeltaZ,2);
    VD FieldSteps = (_bound_right - _bound_left)/_NGrid;
    for (size_t i = 0; i < _NPoint; i++)
    {
        _GridPositions_NoDim.push_back(_LEFT + _DeltaZ*i);
        _FieldValue_NoDim_Current.push_back((_bound_left + FieldSteps*i)/_Scaling);
        _FieldValue_NoDim_Last.push_back((_bound_left + FieldSteps*i)/_Scaling);
    }
    for (size_t i = 0; i < _NGrid; i++)
    {
        _EnergyDensity.push_back(0);
    }
    cout<<"Initial: "<<endl;
    PrintSolitonSolution();
    cout<<_TotalEnergy_Last<<"\t"<<_TotalEnergy_Current<<endl;
}
void SolitonSolver::_Iterating()
{
    for (size_t i = 0; i < _MAXROUNDS; i++)
    {
        // Store the results from last step
        if (((i+1)%1000==0)) 
        {
            cout<<"ROUND: "<<i+1<<endl;
            PrintSolitonSolution();
        }
        for (size_t j = 0; j < _NPoint; j++)
        {
            _FieldValue_NoDim_Last[j] = _FieldValue_NoDim_Current[j];
        }
        // Iterate again;
        for (size_t j = 1; j < _NPoint-1; j++)
        {
            _FieldValue_NoDim_Current[j] = _FieldValue_NoDim_Last[j] + _del_t*(_FieldValue_NoDim_Last[j+1]+_FieldValue_NoDim_Last[j-1]-2*_FieldValue_NoDim_Last[j]);
            _FieldValue_NoDim_Current[j] = _FieldValue_NoDim_Current[j] - _DeltaT*_dpotential(_FieldValue_NoDim_Last[j]*_Scaling,_param)/pow(_Scaling,3);
        }
        // Calculate the Energy_density/Energy, checking the improvement, if too small, jump out of the loop
        _TotalEnergy_Last = _TotalEnergy_Current;
        _TotalEnergy_Current = 0;
        for (size_t j = 0; j < _NGrid; j++)
        {
            _TotalEnergy_Current += _DeltaZ/_Scaling*(_EnergyDensity[j] = _Calc_EnergyDensity(_FieldValue_NoDim_Current[j],_FieldValue_NoDim_Current[j+1]));
        }
        // if (_TotalEnergy_Last != 0)
        // {
        //     cout<<_TotalEnergy_Last<<"\t"<<_TotalEnergy_Current<<endl;
        //     double rel = abs(_TotalEnergy_Current-_TotalEnergy_Last)/_TotalEnergy_Last;
        //     if (rel < _energy_rel_error)
        //     {
        //         break;
        //     }
        // }
    }
}
bool SolitonSolver::Solve()
{
    if (!_potential || !_dpotential || !_param)
    {
        cout<<"At least one of the potential, gradient or parameter is not set!"<<endl;
        return false;
    }
    _Initiative();
    _Iterating();
}
void SolitonSolver::PrintSolitonSolution()
{
    cout<<"The Soliton Solution: "<<endl;
    cout<<"Position_ID\tPosition\t";
    for (size_t i = 0; i < _NFieldDim; i++)
    {
        cout<<"Field_"<<i+1<<"\t";
    }
    cout<<"Energy_Density"<<endl;
    for (size_t i = 0; i < 10; i++)
    {
        cout<<_GridPositions_NoDim[i]<<"\t";
        cout<<_GridPositions_NoDim[i]/_Scaling<<"\t";
        for (size_t j = 0; j < _NFieldDim; j++)
        {
            cout<<_FieldValue_NoDim_Current[i][j]*_Scaling<<"\t";
        }
        if (i < _NGrid)
        {
            cout<<_EnergyDensity[i]<<endl;
        }
        else
        {
            cout<<endl;
        }
    }
    cout<<"......"<<endl;
    for (size_t i = _NPoint-10; i < _NPoint; i++)
    {
        cout<<_GridPositions_NoDim[i]<<"\t";
        cout<<_GridPositions_NoDim[i]/_Scaling<<"\t";
        for (size_t j = 0; j < _NFieldDim; j++)
        {
            cout<<_FieldValue_NoDim_Current[i][j]*_Scaling<<"\t";
        }
        if (i < _NGrid)
        {
            cout<<_EnergyDensity[i]<<endl;
        }
        else
        {
            cout<<endl;
        }
        
    }
    cout<<"Total Energy is: "<<_TotalEnergy_Current<<endl;
}