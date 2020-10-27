/*
	Copyright 2011-2020 Daniel S. Buckstein

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

/*
	animal3D SDK: Minimal 3D Animation Framework
	By Daniel S. Buckstein
	
	a3_HierarchyStateBlend.h
	Hierarchy blend operations.
*/

#ifndef __ANIMAL3D_HIERARCHYSTATEBLEND_H
#define __ANIMAL3D_HIERARCHYSTATEBLEND_H


#include "a3_HierarchyState.h"

#include "a3_Kinematics.h"


#ifdef __cplusplus
extern "C"
{
#else	// !__cplusplus
typedef struct a3_SpatialPoseBlendNode a3_SpatialPoseBlendNode;
typedef struct a3_SpatialPoseBlendTree a3_SpatialPoseBlendTree;
#endif	// __cplusplus


//-----------------------------------------------------------------------------

// execution template
typedef void (*a3_SpatialPoseOpExec)(a3_SpatialPoseBlendNode const* blendNode);
void a3spatialPoseOpExec0C0I(a3_SpatialPoseBlendNode const* blendNode);
void a3spatialPoseOpExec2C1I(a3_SpatialPoseBlendNode const* blendNode);
void a3SpatialPoseTreeExec(a3_SpatialPoseBlendTree const* blendTree);

// operation template for any spatial pose operation
//typedef a3_SpatialPose* (*a3_SpatialPoseOp)(a3_SpatialPose* pose_out); // identity
//typedef a3_SpatialPose* (*a3_SpatialPoseOp)(a3_SpatialPose* pose_out, a3_SpatialPose const* pose_in);
//typedef a3_SpatialPose* (*a3_SpatialPoseOp)(a3_SpatialPose* pose_out, a3_SpatialPose const* pose_lh, a3_SpatialPose const* pose_rh);
//typedef a3_SpatialPose* (*a3_SpatialPoseOp)(a3_SpatialPose* pose_out, a3_SpatialPose const* pose_lh, a3_SpatialPose const* pose_rh, );
typedef a3_SpatialPose* (*a3_SpatialPoseOp)(a3_SpatialPose* pose_out, ...); // ALL OF THEM

//-----------------------------------------------------------------------------

// complete representation of a blend operation
// POINTERS IMPLIES THE THING COMES FROM SOMETHING ELSE
struct a3_SpatialPoseBlendNode
{
	// execution invocation
	a3_SpatialPoseOpExec exec;
	
	// the operation itself
	a3_SpatialPoseOp op;
	
	// output pose
	a3_SpatialPose* pose_out; // exactly 1 ptr/ref to externally-sourced pose (target)

	// control poses
	a3_SpatialPose const* pose_ctrl[16]; // up to 16 ptrs/refs to externally-sourced pose data
	
	// parameters
	a3real const* u[8]; // up to 8 pointers/refs ro externally-sourced params

	// how many of the above
	a3ui16 ctrlCount, paramCount;
};

struct a3_SpatialPoseBlendTree
{
	a3_Hierarchy const* blendTreedDescriptor;

	a3_SpatialPoseBlendNode* nodes;

	// optional: child indices
};

	
//-----------------------------------------------------------------------------
	
// pointer-based reset/identity operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpIdentity(a3_SpatialPose* pose_out);

// pointer-based LERP operation for single spatial pose
a3_SpatialPose* a3spatialPoseOpLERP(a3_SpatialPose* pose_out, a3_SpatialPose const* pose0, a3_SpatialPose const* pose1, a3real const u);


//-----------------------------------------------------------------------------

// data-based reset/identity
a3_SpatialPose a3spatialPoseDOpIdentity();

// data-based LERP
a3_SpatialPose a3spatialPoseDOpLERP(a3_SpatialPose const pose0, a3_SpatialPose const pose1, a3real const u);


//-----------------------------------------------------------------------------

// pointer-based reset/identity operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpIdentity(a3_HierarchyPose* pose_out);

// pointer-based LERP operation for hierarchical pose
a3_HierarchyPose* a3hierarchyPoseOpLERP(a3_HierarchyPose* pose_out, a3_HierarchyPose const* pose0, a3_HierarchyPose const* pose1, a3real const u);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#include "_inl/a3_HierarchyStateBlend.inl"


#endif	// !__ANIMAL3D_HIERARCHYSTATEBLEND_H