#pragma once

/**********************************************
 * A simple high resolution timer
 *********************************************/
double inline CLOCK() {
  timespec ts;
  clock_gettime(CLOCK_REALTIME,&ts);
  return ts.tv_sec+ts.tv_nsec*1e-9;
}

/**********************************************
 *  class for holding profiling data if desired
 *********************************************/

#include <vector>
#include <map>
#include <iostream>
#include <iomanip>

typedef std::map<const char *, double> Event;
typedef std::map<const char *, double>::iterator Eiter;

using std::cout;
using std::endl;
using std::setw;

class levelProfile {
  private:
#ifdef PROFILE
    Event Times;
    Event Tic;
#endif

  public:
    levelProfile() { }
    ~levelProfile() {}

    inline void tic(const char *event)
    {
#ifdef PROFILE
//      cudaThreadSynchronize();
      Tic[event] = CLOCK();
#endif
    }

    inline void toc(const char *event) {
#ifdef PROFILE
//      cudaThreadSynchronize();
      double t = CLOCK();
      Times[event] += t-Tic[event];
#endif
    }

#ifdef PROFILE
    std::vector<const char *>
#else
      void
#endif
      inline getHeaders()
      {
#ifdef PROFILE
        std::vector<const char *> headerVec;
        for (Eiter it=Times.begin(); it!=Times.end(); ++it) {
          headerVec.push_back(it->first);
        }
        return headerVec;
#endif
      }

#ifdef PROFILE
    std::vector<double>
#else
      void
#endif
      inline getTimes()
      {
#ifdef PROFILE
        std::vector<double> times;
        for (Eiter it=Times.begin(); it!=Times.end(); ++it) {
          times.push_back(it->second);
        }
        return times;
#endif
      }

    /********************************************
     * Reset all events
     *******************************************/
    inline void resetTimer() {
#ifdef PROFILE
      for (Eiter it=Times.begin(); it!=Times.end(); ++it) {
        it->second = 0.0;
      }
#endif
    }
};

