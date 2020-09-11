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
	
	a3_KeyframeAnimationController.h
	inline definitions for keyframe animation controller.
*/

#ifdef __ANIMAL3D_KEYFRAMEANIMATIONCONTROLLER_H
#ifndef __ANIMAL3D_KEYFRAMEANIMATIONCONTROLLER_INL
#define __ANIMAL3D_KEYFRAMEANIMATIONCONTROLLER_INL


//-----------------------------------------------------------------------------

// update clip controller
inline a3i32 a3clipControllerUpdate(a3_ClipController* clipCtrl, const a3real dt)
{
	// step/nearest: figure out new time and keyframe0 index
	// lerp: figure out new time (relative to keyframe0)
	//	-> if over, keyframe0 <- keyframe 1, figure out k1
	//	-> if negative, keyframe1 <- keyframe0, figure out the new k0
	// CatmullRom: figure out new time (k0)
	//  -> if over, keyframeP <- keyframe0 <- keyframe1 <- keyframeN
	//		figure out new kN
	//  -> if over, keyframeP -> keyframe0 -> keyframe1 -> keyframeN
	//		figrue out new kP
	
	return -1;
}

// set clip to play
inline a3i32 a3clipControllerSetClip(a3_ClipController* clipCtrl, const a3_ClipPool* clipPool, const a3ui32 clipIndex_pool)
{
	return -1;
}


inline a3i32 a3clipControllerEvaluate(a3_ClipController const* clipCtrl, union a3_Sample* sample_out)
{
	if (clipCtrl &&clipCtrl->clipPtr && sample_out)
	{
		/* 0: step: just return the current keyframe sample
		// no interpolation - step function
		sample_out = clipCtrl->keyframe0Ptr->sample;
		// End step 0 */
		
		/* 1: nearest: if (u < 0.5) ? currentKeyframe : nextKeyframe		
		*sample_out = clipCtrl->keyframeParam < a3real_half
			? clipCtrl->keyframe0Ptr->sample 
			: clipCtrl->keyframe1Ptr->sample;
		// End step 1 */
		
		/* 2: lerp: k0 + (k1 - k0) * u
		sample_out->time = clipCtrl->keyframeTime;
		sample_out->value = a3lerp(
			clipCtrl->keyframe0Ptr->sample.value,
			clipCtrl->keyframe1Ptr->sample.value,
			clipCtrl->keyframeParam);
		// End step 2 */

		//* 3: Catmull-Rom:
		// CatmullRom(kp, k0, k1, kn, u)
		//		kp: keyframe before k0
		//		kn: keyframe after k1
		sample_out->time = clipCtrl->keyframeTime;
		sample_out->value = a3CatmullRom(
			clipCtrl->keyframePPtr->sample.value,
			clipCtrl->keyframe0Ptr->sample.value,
			clipCtrl->keyframe1Ptr->sample.value,
			clipCtrl->keyframeNPtr->sample.value,
			clipCtrl->keyframeParam
		);
		// End Step 3 */

		//* 4: cubic Hermite
		// Hermite(k0, m0, k1, m1, u)
		//		m0 is the rate of change
		// Hermite(k0, h0 - k0, k1, h1 - k1, u)
		sample_out->time = clipCtrl->keyframeTime;
		sample_out->value = a3HermiteControl(
			clipCtrl->keyframe0Ptr->sample.value,
			clipCtrl->keyframe1Ptr->sample.value,
			clipCtrl->keyframe0Ptr->handle.value,
			clipCtrl->keyframe1Ptr->handle.value,
			clipCtrl->keyframeParam
		);

		
		// End Step 4 */


		// done
		return clipCtrl->keyframeIndex0_clip;
	}
	return -1;
}


//-----------------------------------------------------------------------------


#endif	// !__ANIMAL3D_KEYFRAMEANIMATIONCONTROLLER_INL
#endif	// __ANIMAL3D_KEYFRAMEANIMATIONCONTROLLER_H