/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
   Contributing author: Trung Dac Nguyen (ndactrung@gmail.com)
------------------------------------------------------------------------- */

#include "fix_nvt_body.h"
#include <cstring>

#include "group.h"
#include "modify.h"
#include "error.h"


using namespace LAMMPS_NS;
using namespace FixConst;

/* ---------------------------------------------------------------------- */

FixNVTBody::FixNVTBody(LAMMPS *lmp, int narg, char **arg) :
  FixNHBody(lmp, narg, arg)
{
  if (!tstat_flag)
    error->all(FLERR,"Temperature control must be used with fix nvt/body");
  if (pstat_flag)
    error->all(FLERR,"Pressure control can not be used with fix nvt/body");

  // create a new compute temp style
  // id = fix-ID + temp

  std::string tcmd = id + std::string("_temp");
  id_temp = new char[tcmd.size()+1];
  strcpy(id_temp,tcmd.c_str());

  tcmd += fmt::format(" {} temp/body",group->names[igroup]);
  modify->add_compute(tcmd);
  tcomputeflag = 1;
}
