#!/usr/bin/env python

from matplotlib import pyplot as pl
import h5py 

pniio = h5py.File("pniio.nxs")
hdf5  = h5py.File("hdf5.nxs")

wpniio = pniio["/benchmark/data/write"][1:]
whdf5  = hdf5["/benchmark/data/write"][1:]

print "PNIIO average write: ",wpniio.sum()/wpniio.size
print "HDF5 average write:  ",whdf5.sum()/whdf5.size

pl.figure()
pl.plot(wpniio)
pl.plot(whdf5)
pl.legend(("PNIIO","HDF5"))
pl.show()
