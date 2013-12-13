/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of the pni libraries benchmark suite.
 *
 * The PNI libraries benchmark suite is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 2 of the License,
 * or (at your option) any later version.
 *
 * The PNI libraries benchmark suite  is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * the PNI libraries benchmark suite.  If not, see
 * <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 *  Created on: Apr 19, 2011
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#include<cppunit/extensions/HelperMacros.h>
#include<cppunit/TestCaller.h>
#include<cppunit/TestResult.h>
#include<cppunit/TestRunner.h>
#include<cppunit/XmlOutputter.h>
#include<cppunit/TextTestProgressListener.h>
#include<cppunit/ui/text/TextTestRunner.h>
#include<cppunit/extensions/TestFactoryRegistry.h>

#include<cppunit/ui/qt/TestRunner.h>


int main(int argc,char **argv){
    //setup the test runner
    CppUnit::TextTestRunner runner;
    CppUnit::TextTestProgressListener progress;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    
    runner.addTest(registry.makeTest());
    runner.eventManager().addListener(&progress);

    std::ofstream os("benchmark_test.xml");
    runner.setOutputter(new CppUnit::XmlOutputter(&runner.result(),os));
    
    bool result = runner.run();

    return result ? 0 : 1;
}

