//**************************************************************************\
//* This file is property of and copyright by the ALICE Project            *\
//* ALICE Experiment at CERN, All rights reserved.                         *\
//*                                                                        *\
//* Primary Authors: Matthias Richter <Matthias.Richter@ift.uib.no>        *\
//*                  for The ALICE HLT Project.                            *\
//*                                                                        *\
//* Permission to use, copy, modify and distribute this software and its   *\
//* documentation strictly for non-commercial purposes is hereby granted   *\
//* without fee, provided that the above copyright notice appears in all   *\
//* copies and that both the copyright notice and this permission notice   *\
//* appear in the supporting documentation. The authors make no claims     *\
//* about the suitability of this software for any purpose. It is          *\
//* provided "as is" without express or implied warranty.                  *\
//**************************************************************************

/// \file GPUReconstructionKernels.h
/// \author David Rohr

// No header protection, this may be used multiple times
#include "GPUReconstructionKernelMacros.h"

// clang-format off
GPUCA_KRNL_LB((GPUTPCNeighboursFinder                       ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCNeighboursCleaner                      ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCStartHitsFinder                        ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCStartHitsSorter                        ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCTrackletConstructor, singleSlice       ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCTrackletConstructor, allSlices         ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCTrackletSelector                       ), (both), (), ())
GPUCA_KRNL((   GPUMemClean16                                ), (simple, REG, (GPUCA_THREAD_COUNT, 1)), (, GPUPtr1(void*, ptr), unsigned long size), (, GPUPtr2(void*, ptr), size))
GPUCA_KRNL((   GPUTPCGlobalTrackingCopyNumbers              ), (single), (, int n), (, n))
#if !defined(GPUCA_OPENCL1) && (!defined(GPUCA_ALIROOT_LIB) || !defined(GPUCA_GPUCODE))
GPUCA_KRNL_LB((GPUTPCCreateSliceData                        ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCGlobalTracking                         ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerTrackFit                       ), (simple), (, int mode), (, mode))
GPUCA_KRNL_LB((GPUTPCGMMergerFollowLoopers                  ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerUnpackResetIds                 ), (simple), (, int iSlice), (, iSlice))
GPUCA_KRNL_LB((GPUTPCGMMergerSliceRefit                     ), (simple), (, int iSlice), (, iSlice))
GPUCA_KRNL_LB((GPUTPCGMMergerUnpackGlobal                   ), (simple), (, int iSlice), (, iSlice))
GPUCA_KRNL((   GPUTPCGMMergerUnpackSaveNumber               ), (simple), (, int id), (, id))
GPUCA_KRNL_LB((GPUTPCGMMergerResolve, step0                 ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerResolve, step1                 ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerResolve, step2                 ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerResolve, step3                 ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerResolve, step4                 ), (simple), (, char useOrigTrackParam, char mergeAll), (, useOrigTrackParam, mergeAll))
GPUCA_KRNL_LB((GPUTPCGMMergerClearLinks                     ), (simple), (, char nOutput), (, nOutput))
GPUCA_KRNL_LB((GPUTPCGMMergerMergeWithinPrepare             ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerMergeSlicesPrepare             ), (simple), (, int border0, int border1, char useOrigTrackParam), (, border0, border1, useOrigTrackParam))
GPUCA_KRNL_LB((GPUTPCGMMergerMergeBorders, step0            ), (simple), (, int iSlice, char withinSlice, char mergeMode), (, iSlice, withinSlice, mergeMode))
GPUCA_KRNL((   GPUTPCGMMergerMergeBorders, step1            ), (simple), (, int iSlice, char withinSlice, char mergeMode), (, iSlice, withinSlice, mergeMode))
GPUCA_KRNL_LB((GPUTPCGMMergerMergeBorders, step2            ), (simple), (, int iSlice, char withinSlice, char mergeMode), (, iSlice, withinSlice, mergeMode))
GPUCA_KRNL((   GPUTPCGMMergerMergeBorders, variant          ), (simple), (, GPUPtr1(gputpcgmmergertypes::GPUTPCGMBorderRange*, range), int N, int cmpMax), (, GPUPtr2(gputpcgmmergertypes::GPUTPCGMBorderRange*, range), N, cmpMax))
GPUCA_KRNL_LB((GPUTPCGMMergerMergeCE                        ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerLinkGlobalTracks               ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerCollect                        ), (simple), (), ())
GPUCA_KRNL((   GPUTPCGMMergerSortTracks                     ), (simple), (), ())
GPUCA_KRNL((   GPUTPCGMMergerSortTracksQPt                  ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerSortTracksPrepare              ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerPrepareClusters, step0         ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerPrepareClusters, step1         ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerPrepareClusters, step2         ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerFinalize, step0                ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerFinalize, step1                ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerFinalize, step2                ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerMergeLoopers, step0            ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerMergeLoopers, step1            ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMMergerMergeLoopers, step2            ), (simple), (), ())
#ifdef GPUCA_HAVE_O2HEADERS
GPUCA_KRNL_LB((GPUTPCGMO2Output, prepare                    ), (simple), (), ())
GPUCA_KRNL((   GPUTPCGMO2Output, sort                       ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCGMO2Output, output                     ), (simple), (), ())
GPUCA_KRNL((   GPUTPCGMO2Output, mc                         ), (simple), (), ())
GPUCA_KRNL_LB((GPUTRDTrackerKernels, gpuVersion             ), (simple), (, GPUPtr1(GPUTRDTrackerGPU*, externalInstance)), (, GPUPtr2(GPUTRDTrackerGPU*, externalInstance)))
GPUCA_KRNL_LB((GPUTRDTrackerKernels, o2Version              ), (simple), (, GPUPtr1(GPUTRDTracker*, externalInstance)), (, GPUPtr2(GPUTRDTracker*, externalInstance)))
GPUCA_KRNL_LB((GPUITSFitterKernel                           ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCConvertKernel                          ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCCompressionKernels, step0attached      ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCCompressionKernels, step1unattached    ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCCompressionGatherKernels, unbuffered   ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCCompressionGatherKernels, buffered32   ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCCompressionGatherKernels, buffered64   ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCCompressionGatherKernels, buffered128  ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCCompressionGatherKernels, multiBlock   ), (simple), (), ())
GPUCA_KRNL_LB((GPUTPCCFCheckPadBaseline                     ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCCFChargeMapFiller, fillIndexMap        ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCCFChargeMapFiller, fillFromDigits      ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCCFChargeMapFiller, findFragmentStart   ), (single), (, char setPositions), (, setPositions))
GPUCA_KRNL_LB((GPUTPCCFPeakFinder                           ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCCFNoiseSuppression, noiseSuppression   ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCCFNoiseSuppression, updatePeaks        ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCCFDeconvolution                        ), (single), (), ())
GPUCA_KRNL_LB((GPUTPCCFClusterizer                          ), (single), (, char onlyMC), (, onlyMC))
GPUCA_KRNL((   GPUTPCCFMCLabelFlattener, setRowOffsets      ), (single), (), ())
GPUCA_KRNL((   GPUTPCCFMCLabelFlattener, flatten            ), (single), (, GPUPtr1(GPUTPCLinearLabels*, out)), (, GPUPtr2(GPUTPCLinearLabels*, out)))
GPUCA_KRNL_LB((GPUTPCCFStreamCompaction, scanStart          ), (single), (, int iBuf, int stage), (, iBuf, stage))
GPUCA_KRNL_LB((GPUTPCCFStreamCompaction, scanUp             ), (single), (, int iBuf, int nElems), (, iBuf, nElems))
GPUCA_KRNL_LB((GPUTPCCFStreamCompaction, scanTop            ), (single), (, int iBuf, int nElems), (, iBuf, nElems))
GPUCA_KRNL_LB((GPUTPCCFStreamCompaction, scanDown           ), (single), (, int iBuf, unsigned int offset, int nElems), (, iBuf, offset, nElems))
GPUCA_KRNL_LB((GPUTPCCFStreamCompaction, compactDigits      ), (single), (, int iBuf, int stage, GPUPtr1(ChargePos*, in), GPUPtr1(ChargePos*, out)), (, iBuf, stage, GPUPtr2(ChargePos*, in), GPUPtr2(ChargePos*, out)))
GPUCA_KRNL_LB((GPUTPCCFDecodeZS                             ), (single), (, int firstHBF), (, firstHBF))
GPUCA_KRNL_LB((GPUTPCCFGather                               ), (single), (, GPUPtr1(o2::tpc::ClusterNative*, dest)), (, GPUPtr2(o2::tpc::ClusterNative*, dest)))
GPUCA_KRNL_LB((GPUTrackingRefitKernel, mode0asGPU           ), (simple), (), ())
GPUCA_KRNL_LB((GPUTrackingRefitKernel, mode1asTrackParCov   ), (simple), (), ())
#endif
#endif
// clang-format on
