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

/// \file GPUReconstructionDeviceBase.h
/// \author David Rohr

#ifndef GPURECONSTRUCTIONDEVICEBASE_H
#define GPURECONSTRUCTIONDEVICEBASE_H

#include "GPUReconstructionCPU.h"
#include <pthread.h>
#include "GPUReconstructionHelpers.h"
#include "GPUChain.h"

namespace GPUCA_NAMESPACE
{
namespace gpu
{
#if !(defined(__CINT__) || defined(__ROOTCINT__) || defined(__CLING__) || defined(__ROOTCLING__) || defined(G__ROOT))
extern template class GPUReconstructionKernels<GPUReconstructionCPUBackend>;
#endif

class GPUReconstructionDeviceBase : public GPUReconstructionCPU
{
 public:
  ~GPUReconstructionDeviceBase() override;

  const GPUParam* DeviceParam() const { return &mDeviceConstantMem->param; }

 protected:
  GPUReconstructionDeviceBase(const GPUSettingsDeviceBackend& cfg, size_t sizeCheck);

  int InitDevice() override;
  virtual int InitDevice_Runtime() = 0;
  int ExitDevice() override;
  virtual int ExitDevice_Runtime() = 0;
  int registerMemoryForGPU(const void* ptr, size_t size) override;
  int unregisterMemoryForGPU(const void* ptr) override;

  virtual const GPUTPCTracker* CPUTracker(int iSlice) { return &processors()->tpcTrackers[iSlice]; }

  int GPUDebug(const char* state = "UNKNOWN", int stream = -1, bool force = false) override = 0;
  size_t TransferMemoryInternal(GPUMemoryResource* res, int stream, deviceEvent* ev, deviceEvent* evList, int nEvents, bool toGPU, const void* src, void* dst) override = 0;
  size_t GPUMemCpy(void* dst, const void* src, size_t size, int stream, int toGPU, deviceEvent* ev = nullptr, deviceEvent* evList = nullptr, int nEvents = 1) override = 0;
  size_t GPUMemCpyAlways(bool onGpu, void* dst, const void* src, size_t size, int stream, int toGPU, deviceEvent* ev = nullptr, deviceEvent* evList = nullptr, int nEvents = 1) override;
  size_t WriteToConstantMemory(size_t offset, const void* src, size_t size, int stream = -1, deviceEvent* ev = nullptr) override = 0;

  int StartHelperThreads() override;
  int StopHelperThreads() override;
  void RunHelperThreads(int (GPUReconstructionHelpers::helperDelegateBase::*function)(int, int, GPUReconstructionHelpers::helperParam*), GPUReconstructionHelpers::helperDelegateBase* functionCls, int count) override;
  int HelperError(int iThread) const override { return mHelperParams[iThread].error; }
  int HelperDone(int iThread) const override { return mHelperParams[iThread].done; }
  void WaitForHelperThreads() override;
  void ResetHelperThreads(int helpers) override;
  void ResetThisHelperThread(GPUReconstructionHelpers::helperParam* par);

  int GetGlobalLock(void*& pLock);
  void ReleaseGlobalLock(void* sem);

  static void* helperWrapper_static(void* arg);
  void* helperWrapper(GPUReconstructionHelpers::helperParam* par);

  int mDeviceId = -1;                                             // Device ID used by backend
  GPUReconstructionHelpers::helperParam* mHelperParams = nullptr; // Control Struct for helper threads
  int mNSlaveThreads = 0;                                         // Number of slave threads currently active

  struct DebugEvents {
    void *DebugStart, *DebugStop; // Debug timer events
  };
  DebugEvents* mDebugEvents = nullptr;
};

inline size_t GPUReconstructionDeviceBase::GPUMemCpyAlways(bool onGpu, void* dst, const void* src, size_t size, int stream, int toGPU, deviceEvent* ev, deviceEvent* evList, int nEvents)
{
  if (onGpu) {
    return GPUMemCpy(dst, src, size, stream, toGPU, ev, evList, nEvents);
  } else {
    return GPUReconstructionCPU::GPUMemCpyAlways(false, dst, src, size, stream, toGPU, ev, evList, nEvents);
  }
}
} // namespace gpu
} // namespace GPUCA_NAMESPACE

#endif
