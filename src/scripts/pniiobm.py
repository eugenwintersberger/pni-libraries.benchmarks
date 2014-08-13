#!/usr/bin/env python

from matplotlib import pyplot as pl
import h5py 

pniio = h5py.File("pniio.nxs")
hdf5  = h5py.File("hdf5.nxs")

wpniio = pniio["/benchmark/data/write"][1:]
whdf5  = hdf5["/benchmark/data/write"][1:]

wpniio_av = float(wpniio.sum())/float(wpniio.size)
whdf5_av  = float(whdf5.sum())/float(whdf5.size)
print "PNIIO average write: {:e}".format(wpniio_av)
print "HDF5 average write:  {:e}".format(whdf5_av)
print "Ratio (PNIIO/HDF5):  {:e}".format(wpniio_av/whdf5_av)

pl.figure()
pl.plot(wpniio,lw=1.5)
pl.plot(whdf5,lw=1.5)
pl.legend(("PNIIO","HDF5"))
pl.ylabel("write time ("+pniio["/benchmark/data/write"].attrs["units"]+")")
pl.xlabel("run number")
pl.axhline(y=wpniio_av,ls="--")
pl.axhline(y=whdf5_av,ls="--")
pl.show()
