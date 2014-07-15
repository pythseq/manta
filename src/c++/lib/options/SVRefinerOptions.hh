// -*- mode: c++; indent-tabs-mode: nil; -*-
//
// Manta
// Copyright (c) 2013-2014 Illumina, Inc.
//
// This software is provided under the terms and conditions of the
// Illumina Open Source Software License 1.
//
// You should have received a copy of the Illumina Open Source
// Software License 1 along with this program. If not, see
// <https://github.com/sequencing/licenses/>
//

///
/// \author Chris Saunders
///

#pragma once

#include "alignment/AlignmentScores.hh"
#include "options/IterativeAssemblerOptions.hh"
#include "options/SmallAssemblerOptions.hh"

//#define ITERATIVE_ASSEMBLER
#ifdef ITERATIVE_ASSEMBLER
typedef IterativeAssemblerOptions AssemblerOptions;
#else
typedef SmallAssemblerOptions AssemblerOptions;
#endif

namespace SUPERTMP
{
static const int largeGapOpenScore(-24);
}


/// Options for the SV refiner step
///
/// Note that we have two categories of options for assembly and alignment,
/// one for small events, and one for large events
///
struct SVRefinerOptions
{
    /// match, mismatch, open score ratios taken from bwa defaults (but not extend!) :
    ///
    SVRefinerOptions() :
        smallSVAlignScores(2, -8, -12, 0, -1),
        largeSVAlignScores(2, -8, -18, -1, -1),
        largeInsertEdgeAlignScores(2, -8, -18, -1, -1),
        largeInsertCompleteAlignScores(2, -8,  SUPERTMP::largeGapOpenScore, 0, -1),
        spanningAlignScores(2, -8, -12, -1, -1),
        largeGapOpenScore(SUPERTMP::largeGapOpenScore),
        jumpScore(-25),
        RNAspanningAlignScores(2, -8, -19, -1, -1),
        RNAIntronOpenScore(-15),
        RNAIntronOffEdgeScore(0)
    {
        spanningAssembleOpt.minContigLength=75; ///< For breakend-spanning assemblies we require a larger contig than for small-variant assemblies
    }

    /// parameters for small SV assembly/alignment:
    AlignmentScores<int> smallSVAlignScores;
    AlignmentScores<int> largeSVAlignScores; // large SV but at a single assembly locus
    AlignmentScores<int> largeInsertEdgeAlignScores;
    AlignmentScores<int> largeInsertCompleteAlignScores;
    AssemblerOptions smallSVAssembleOpt;

    // parameters for large SV assembly/alignment:
    AlignmentScores<int> spanningAlignScores;
    const int largeGapOpenScore;
    const int jumpScore;
    AlignmentScores<int> RNAspanningAlignScores;
    const int RNAIntronOpenScore;
    const int RNAIntronOffEdgeScore;
    AssemblerOptions spanningAssembleOpt;
};
