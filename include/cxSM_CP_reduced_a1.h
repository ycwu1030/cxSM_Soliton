#ifndef CXSM_CP_REDUCED_A1
#define CXSM_CP_REDUCED_A1

#include "cxSM_CP.h"
#include <iostream>
#include <iomanip>

class cxSM_CP_reduced_a1: public cxSM_CP
{
// ! Note that, in this version, the DW/soliton ODEs are solved in terms of vev, Re(vs), Im(vs), not vev, |vs|, alpha !
protected:
// * V = mu2 |Phi|^2 + lam |Phi|^4 + del2/2 |Phi|^2|S|^2 + b2/2 |S|^2 + d2/4 |S|^4 
// * + ( b1/4 S^2 + a1 S + c.c)
// Potential Parameter
    // * Inherit from cxSM_CP
    // double _mu2; //- Z2
    // double _lam; //- Z2
    // double _del2; //- Z2
    // double _b2; //- Z2
    // double _d2; //- Z2
    // double _del3; // Should be zero
    // double _b1;
    // double _d1; // Should be zero
    // double _d3; // Should be zero
    double _a1;

// Physical Parameter
    // * Inherit from cxSM_CP
    // double _MHL;
    // double _MHH;
    // double _MHA;
    // double _vev;
    // double _vsr;
    // double _vsi;
    // double _theta1;
    // double _theta2;
    // double _theta3;

    // double _MHL2;
    // double _MHH2;
    // double _MHA2;

// Another way as vs and alpha:
    // * Inherit from cxSM_CP
    // double _vs;
    // double _alpha;

// The mixing matrix elements
    // * Inherit from cxSM_CP;
    // Eigen::Matrix3d _R;


// Local parameter store local extreme points
    // From cxSM_Z2, no need to redefine;

private:
    bool _GetAlphaTheta2(const double MHH, const double MHA, const double theta1, double theta3, double &alpha, double &theta2);
    void _GetR();
    void _GetThetas();

public:
    cxSM_CP_reduced_a1();
    ~cxSM_CP_reduced_a1(){};

    void Set_Potential_Parameters(double mu2, double lam, double del2, double b2, double d2, double a1, double b1);
    bool Set_Physical_Parameters(double vsr, double vsi, double MHH, double MHA, double theta1, double theta2, double theta3);
    bool Set_Physical_Parameters_vs_theta(double vs, double MHH, double MHA, double theta1, double theta3);
    bool Set_Physical_Parameters_vsr_theta(double vsr, double MHH, double MHA, double theta1, double theta3);
    bool Set_Physical_Parameters_vsi_theta(double vsi, double MHH, double MHA, double theta1, double theta3);

    void GetVS(double &vs_real, double &vs_img){vs_real = _vsr; vs_img = _vsi;};
    void GetTheta(int id, double &theta)
    {
        switch (id)
        {
        case 1:
            theta = _theta1;
            return;
        case 2:
            theta = _theta2;
            return;
        case 3:
            theta = _theta3;
            return;
        default:
            theta = _theta2;
            return;
        }
    }
    friend std::ostream &operator<<(std::ostream &os, const cxSM_CP_reduced_a1 &mod){
        os << std::scientific<<std::setprecision(10);
        os << mod._MHL << "\t" << mod._MHH << "\t" << mod._MHA << "\t" << mod._vs;
        os << "\t" << mod._theta1 << "\t" << mod._theta2 << "\t" << mod._theta3;
        os << "\t" << mod._mu2 << "\t" << mod._b2;
        os << "\t" << mod._lam << "\t" << mod._del2 << "\t" << mod._d2;
        os << "\t" << mod._a1 << "\t" << mod._b1 << "\t" << mod._alpha;
        return os;
    };
    // * Inherit from cxSM_CP
    virtual double Vtotal(VD field_values, double scale = 1);
    virtual VD dVtotal(VD field_values, double scale = 1);
    virtual double V0_global(double scale = 1);

    virtual void FindLocalMinima();

    virtual void PrintParameters();

};

#endif //CXSM_CP_REDUCED_A1