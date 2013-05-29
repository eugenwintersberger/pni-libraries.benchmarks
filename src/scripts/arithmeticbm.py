#!/usr/bin/env python

import numpy 
from optparse import OptionParser
import time

class benchmark_result(object):
    def __init__(self):
        self._start_time = 0
        self._stop_time  = 0

    def _get_start(self):
        return self._start_time

    def _set_start(self,value):
        self._start_time = value

    def _get_stop(self):
        return self._stop_time

    def _set_stop(self,value):
        self._stop_time = value

    def _get_duration(self):
        return self._stop_time - self._start_time


    start_time = property(_get_start,_set_start)
    stop_time  = property(_get_stop,_set_stop)
    duration   = property(_get_duration)

def average_result(runner):

    av_result = benchmark_result()
    for result in runner:
        av_result.start_time += result.start_time
        av_result.stop_time  += result.stop_time

    av_result.start_time /= len(runner)
    av_result.stop_time  /= len(runner)

    return av_result



class benchmark_runner(object):
    def __init__(self):
        self._result_list = []
    
    def __getitem__(self,index):
        return self._result_list[index]

    def __iter__(self):
        return self._result_list.__iter__()

    def __len__(self):
        return len(self._result_list)

    def run(self,nr,func):
        
        for i in range(nr):
            r = benchmark_result()

            r.start_time = time.time()
            func()
            r.stop_time = time.time()

            self._result_list.append(r)


class benchmark(object):
    def __init__(self,nx,ny):
        self._a = numpy.random.random_sample((nx,ny)).astype("float64")
        self._b = numpy.random.random_sample((nx,ny)).astype("float64")
        self._c = numpy.random.random_sample((nx,ny)).astype("float64")
        self._d = numpy.random.random_sample((nx,ny)).astype("float64")
        self._e = numpy.random.random_sample((nx,ny)).astype("float64")
        self._f = numpy.random.random_sample((nx,ny)).astype("float64")

class add_benchmark(benchmark):
    def __intit__(self,nx,ny):
        benchmark.__init__(self,nx,ny)


    def __call__(self):
        self._c = self._a + self._b

class sub_benchmark(benchmark):
    def __init__(self,nx,ny):
        benchmark.__init__(self,nx,ny)

    def __call__(self):
        self._c = self._a - self._b

class div_benchmark(benchmark):
    def __init__(self,nx,ny):
        benchmark.__init__(self,nx,ny)

    def __call__(self):
        self._c = self._a/self._b

class mult_benchmark(benchmark):
    def __init__(self,nx,ny):
        benchmark.__init__(self,nx,ny)

    def __call__(self):
        self._c = self._a*self._b

class all_benchmark(benchmark):
    def __init__(self,nx,ny):
        benchmark.__init__(self,nx,ny)

    def __call__(self):
        self._c = (self._a*self._b)+(self._d-self._e)/self._f

       

parser = OptionParser()

parser.add_option("-x","--nx",dest="nx",action="store",type="int",
                  default=1024,
                  help="number of points along x")
parser.add_option("-y","--ny",dest="ny",action="store",type="int",
                  default="1024",
                  help="number of point along y")
parser.add_option("-r","--nruns",dest="nruns",action="store",type="int",
                  default=1,
                  help="number of runs")


(options,args) = parser.parse_args()


#create benchmarks
add_bm = add_benchmark(options.nx,options.ny)
sub_bm = sub_benchmark(options.nx,options.ny)
div_bm = div_benchmark(options.nx,options.ny)
mult_bm = mult_benchmark(options.nx,options.ny)
all_bm = all_benchmark(options.nx,options.ny)


runner = benchmark_runner()
runner.run(options.nruns,add_bm)
add_bm_result = average_result(runner)

runner = benchmark_runner()
runner.run(options.nruns,sub_bm)
sub_bm_result = average_result(runner)

runner = benchmark_runner()
runner.run(options.nruns,mult_bm)
mult_bm_result = average_result(runner)

runner = benchmark_runner()
runner.run(options.nruns,div_bm)
div_bm_result = average_result(runner)

runner = benchmark_runner()
runner.run(options.nruns,all_bm)
all_bm_result = average_result(runner)

print "(a+b):         ",add_bm_result.duration
print "(a-b):         ",sub_bm_result.duration
print "(a*b):         ",mult_bm_result.duration
print "(a/b):         ",div_bm_result.duration
print "(a*b)+(d-e)/f: ",all_bm_result.duration
