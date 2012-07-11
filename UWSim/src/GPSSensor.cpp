/*
 * GPSSensor.cpp
 *
 *  Created on: 03/07/2012
 *      Author: mprats
 */

#include "UWSimUtils.h"
#include "GPSSensor.h"
#include <osg/io_utils>

osg::Vec3d GPSSensor::getMeasurement() {
	//Should get world coords and then transform to the localizedWorld
	osg::Matrixd *rMs=getWorldCoords(node_);
	osg::Matrixd lMs=*rMs*osg::Matrixd::inverse(rMl_);

	//Now add some gaussian noise
	static boost::normal_distribution<> normal(0,std_);
	static boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > var_nor(rng_, normal);

	return lMs.getTrans()+osg::Vec3d(var_nor(), var_nor(), var_nor());
}


double GPSSensor::depthBelowWater() {
	osg::Matrixd *rMs=getWorldCoords(node_);
	return -(rMs->getTrans().z()-oscene_->getOceanScene()->getOceanSurfaceHeight());
}