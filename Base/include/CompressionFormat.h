/* FasTC
 * Copyright (c) 2013 University of North Carolina at Chapel Hill.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for educational, research, and non-profit purposes, without
 * fee, and without a written agreement is hereby granted, provided that the
 * above copyright notice, this paragraph, and the following four paragraphs
 * appear in all copies.
 *
 * Permission to incorporate this software into commercial products may be
 * obtained by contacting the authors or the Office of Technology Development
 * at the University of North Carolina at Chapel Hill <otd@unc.edu>.
 *
 * This software program and documentation are copyrighted by the University of
 * North Carolina at Chapel Hill. The software program and documentation are
 * supplied "as is," without any accompanying services from the University of
 * North Carolina at Chapel Hill or the authors. The University of North
 * Carolina at Chapel Hill and the authors do not warrant that the operation of
 * the program will be uninterrupted or error-free. The end-user understands
 * that the program was developed for research purposes and is advised not to
 * rely exclusively on the program for any reason.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE
 * AUTHORS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF
 * THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA
 * AT CHAPEL HILL OR THE AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY
 * DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY 
 * STATUTORY WARRANTY OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS ON
 * AN "AS IS" BASIS, AND THE UNIVERSITY  OF NORTH CAROLINA AT CHAPEL HILL AND
 * THE AUTHORS HAVE NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, 
 * ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Please send all BUG REPORTS to <pavel@cs.unc.edu>.
 *
 * The authors may be contacted via:
 *
 * Pavel Krajcevski
 * Dept of Computer Science
 * 201 S Columbia St
 * Frederick P. Brooks, Jr. Computer Science Bldg
 * Chapel Hill, NC 27599-3175
 * USA
 * 
 * <http://gamma.cs.unc.edu/FasTC/>
 */

#ifndef _BASE_INCLUDE_COMPRESSIONFORMAT_H_
#define _BASE_INCLUDE_COMPRESSIONFORMAT_H_

#include "TexCompTypes.h"

namespace FasTC {

  // The different supported compression formats
  enum ECompressionFormat {
    eCompressionFormat_DXT1,
    eCompressionFormat_DXT5,
    eCompressionFormat_ETC1,
    eCompressionFormat_BPTC,
    eCompressionFormat_PVRTC,

    kNumCompressionFormats
  };

  // Returns the dimensions of the blocks for the given format.
  inline static void GetBlockDimensions(ECompressionFormat fmt, uint32 (&outSz)[2]) {
    switch(fmt) {
      default:
      case eCompressionFormat_DXT1:
      case eCompressionFormat_DXT5:
      case eCompressionFormat_BPTC:
      case eCompressionFormat_PVRTC:
      case eCompressionFormat_ETC1:
        outSz[0] = 4;
        outSz[1] = 4;
        break;
    }
  }

  // Returns the size of the compressed block in bytes for the given format.
  inline static uint32 GetBlockSize(ECompressionFormat fmt) {
    switch(fmt) {
      default:
      case eCompressionFormat_DXT1:
      case eCompressionFormat_PVRTC:
      case eCompressionFormat_ETC1:
        return 8;
        break;

      case eCompressionFormat_DXT5:
      case eCompressionFormat_BPTC:
        return 16;
    }
  }
}  // namespace FasTC

#endif // _BASE_INCLUDE_COMPRESSIONFORMAT_H_
