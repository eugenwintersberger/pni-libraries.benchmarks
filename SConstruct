import os

env = Environment()


#set global compiler options
env.AppendUnique(CPPFLAGS=['-std=c++0x'])
env.AppendUnique(CPPFLAGS=['-O3'])


try:
    env['ENV']['PKG_CONFIG_PATH'] = os.environ['PKG_CONFIG_PATH']
except:
    print "no custom pkg-config path found ..."

pnicore_build = env.Clone()
pniio_build = env.Clone()

try:
    pnicore_build.ParseConfig('pkg-config --cflags --libs pnicore')
except:
    pass


try:
    pniio_build.ParseConfig('pkg-config --cflags --libs pniio')
except:
    pass




Export('pnicore_build')
Export('pniio_build')
#build pnicore benchmarks
SConscript('src/pnicore/SConscript')
SConscript('src/pniio/SConscript')
