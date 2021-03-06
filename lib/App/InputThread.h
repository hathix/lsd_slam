#pragma once

#include "IOWrapper/OutputIOWrapper.h"

#include "util/ThreadMutexObject.h"

#include "SlamSystem.h"

#include "libvideoio/DataSource.h"
#include "libvideoio/Undistorter.h"

namespace lsd_slam {

  class InputThread {
  public:

    InputThread(  std::shared_ptr<lsd_slam::SlamSystem> &system,
                   std::shared_ptr<libvideoio::DataSource> &dataSource,
                   std::shared_ptr<libvideoio::Undistorter> &undistorter );

    void setIOOutputWrapper( const std::shared_ptr<lsd_slam::OutputIOWrapper> &out );

    // Entry point for boost::thread
    void operator()();

    std::shared_ptr<lsd_slam::SlamSystem> &system;
    std::shared_ptr<libvideoio::DataSource> dataSource;
    std::shared_ptr<libvideoio::Undistorter> undistorter;

    ThreadMutexObject<bool> inputDone;
    ThreadSynchronizer inputReady;

  protected:
    std::shared_ptr<lsd_slam::OutputIOWrapper> output;

  };
}
