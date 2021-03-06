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

#include "gtest/gtest.h"
#include "Pixel.h"

TEST(Pixel, DefaultConstructor) {
  FasTC::Pixel p;
  EXPECT_EQ(p.R(), 0);
  EXPECT_EQ(p.G(), 0);
  EXPECT_EQ(p.B(), 0);
  EXPECT_EQ(p.A(), 0);

  uint8 depth[4];
  p.GetBitDepth(depth);

  for(int i = 0; i < 4; i++) {
    EXPECT_EQ(depth[i], 8);
  }
}

TEST(Pixel, FromBitsAndAssociatedConstructor) {
  const uint8 bits[8] = { 0xA8, 0xB3, 0x7C, 0x21, 0xBD, 0xD4, 0x09, 0x92 };
  FasTC::Pixel ps[2];
  ps[0] = FasTC::Pixel(bits);
  ps[1].FromBits(bits);

  for(int i = 0; i < 2; i++) {
    FasTC::Pixel &p = ps[i];

    EXPECT_EQ(p.A(), 0xA8);
    EXPECT_EQ(p.R(), 0xB3);
    EXPECT_EQ(p.G(), 0x7C);
    EXPECT_EQ(p.B(), 0x21);

    uint8 depth[4];
    p.GetBitDepth(depth);
    for(int j = 0; j < 4; j++) {
      EXPECT_EQ(depth[j], 8);
    }
  }

  const uint8 depth1[4] = { 3, 2, 0, 8 };
  ps[0] = FasTC::Pixel(bits + 3, depth1);
  ps[1].FromBits(bits + 3, depth1);

  for(int i = 0; i < 2; i++) {
    FasTC::Pixel &p = ps[i];

    EXPECT_EQ(p.A(), 0x01);
    EXPECT_EQ(p.R(), 0x00);
    EXPECT_EQ(p.G(), 0xFF);
    EXPECT_EQ(p.B(), 0x37);

    uint8 depth[4];
    p.GetBitDepth(depth);

    EXPECT_EQ(depth[0], 3);
    EXPECT_EQ(depth[1], 2);
    EXPECT_EQ(depth[2], 0);
    EXPECT_EQ(depth[3], 8);
  }


  const uint8 depth2[4] = { 5, 6, 2, 4 };
  ps[0] = FasTC::Pixel(bits + 4, depth2, 2);
  ps[1].FromBits(bits + 4, depth2, 2);

  for(int i = 0; i < 2; i++) {
    FasTC::Pixel &p = ps[i];

    EXPECT_EQ(p.A(), 0x1E);
    EXPECT_EQ(p.R(), 0x3A);
    EXPECT_EQ(p.G(), 0x02);
    EXPECT_EQ(p.B(), 0x00);

    uint8 depth[4];
    p.GetBitDepth(depth);

    EXPECT_EQ(depth[0], 5);
    EXPECT_EQ(depth[1], 6);
    EXPECT_EQ(depth[2], 2);
    EXPECT_EQ(depth[3], 4);
  }
}

TEST(Pixel, ToBits) {
  FasTC::Pixel p;

  uint8 bitDepth[4] = { 2, 8, 1, 7 };
  p.ChangeBitDepth(bitDepth);

  p.A() = 0x2;
  p.R() = 0x56;
  p.G() = 0;
  p.B() = 0x4F;

  uint8 bits[3];
  memset(bits, 0, sizeof(bits));
  p.ToBits(bits, sizeof(bits));

  EXPECT_EQ(bits[0], 0x4F);
  EXPECT_EQ(bits[1], 0x56);
  EXPECT_EQ(bits[2], 0x2);

  memset(bits, 0, sizeof(bits));
  p.ToBits(bits, 3, 2);
  EXPECT_EQ(bits[0], 0x3C);
  EXPECT_EQ(bits[1], 0x59);
  EXPECT_EQ(bits[2], 0x09);
}

TEST(Pixel, ChangeChannelBitDepth) {
  uint8 val = 0x43;
  uint8 depth = 7;

  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 8), 0x87);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 7), 0x43);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 6), 0x22);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 2), 0x2);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 0), 0xFF);

  val = 0x3;
  depth = 3;

  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 8), 0x6D);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 6), 0x1B);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 3), 0x03);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 2), 0x02);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 0), 0xFF);
}

TEST(Pixel, ChangeChannelBitDepthFromZero) {
  uint8 val = 0x43;
  uint8 depth = 0;

  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 8), 0xFF);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 7), 0x7F);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 6), 0x3F);
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 2), 0x03);

  // Shouldn't change it...
  EXPECT_EQ(FasTC::Pixel::ChangeBitDepth(val, depth, 0), 0x43);
}

TEST(Pixel, ChangePixelBitDepth) {
  const uint8 bits[4] = { 0x86, 0xC0, 0x0, 0x0 };
  const uint8 depth[4] = {7, 3, 0, 0};
  FasTC::Pixel p(bits, depth);

  const uint8 newDepth[4] = { 8, 8, 8, 8 };
  p.ChangeBitDepth(newDepth);

  EXPECT_EQ(p.A(), 0x87);
  EXPECT_EQ(p.R(), 0x6D);
  EXPECT_EQ(p.G(), 0xFF);
  EXPECT_EQ(p.B(), 0xFF);

  uint8 outDepth[4];
  p.GetBitDepth(outDepth);

  for(uint32 i = 0; i < 4; i++) {
    EXPECT_EQ(outDepth[i], 8);
  }
}

TEST(Pixel, PackRGBA) {
  const uint8 bits[4] = { 0x86, 0xC0, 0x0, 0x0 };
  const uint8 depth[4] = {7, 3, 0, 0};
  FasTC::Pixel p(bits, depth);

  uint32 val = p.Pack();
  EXPECT_EQ(val, 0x87FFFF6D);
}

TEST(Pixel, UnpackRGBA) {
  uint32 rgba = 0x4619B3FE;
  FasTC::Pixel p;

  p.Unpack(rgba);
  EXPECT_EQ(p.A(), 0x46);
  EXPECT_EQ(p.B(), 0x19);
  EXPECT_EQ(p.G(), 0xB3);
  EXPECT_EQ(p.R(), 0xFE);

  p = FasTC::Pixel(rgba);
  EXPECT_EQ(p.A(), 0x46);
  EXPECT_EQ(p.B(), 0x19);
  EXPECT_EQ(p.G(), 0xB3);
  EXPECT_EQ(p.R(), 0xFE);

  p = FasTC::Pixel();
  uint8 newBitDepth[4] = { 3, 5, 2, 1 };  // A R G B
  p.ChangeBitDepth(newBitDepth);
  p.Unpack(rgba);

  EXPECT_EQ(p.A(), 0x2);
  EXPECT_EQ(p.B(), 0x0);
  EXPECT_EQ(p.G(), 0x3);
  EXPECT_EQ(p.R(), 0x1f);
}

TEST(Pixel, ScaleColor) {
  FasTC::Pixel p;
  uint8 newBitDepth[4] = { 3, 5, 2, 1 };  // A R G B
  p.ChangeBitDepth(newBitDepth);
  
  p.R() = 1;
  p.G() = 2;
  p.B() = 3;
  p.A() = 4;

  FasTC::Pixel sp = p * 3;
  FasTC::Pixel ps = 3 * p;

  EXPECT_EQ(sp.R(), 3); EXPECT_EQ(ps.R(), 3);
  EXPECT_EQ(sp.G(), 6); EXPECT_EQ(ps.G(), 6);
  EXPECT_EQ(sp.B(), 9); EXPECT_EQ(ps.B(), 9);
  EXPECT_EQ(sp.A(), 12); EXPECT_EQ(ps.A(), 12);

  uint8 bd[4];
  sp.GetBitDepth(bd);
  for(uint32 i = 0; i < 4; i++) {
    EXPECT_EQ(bd[i], newBitDepth[i]);
  }

  ps.GetBitDepth(bd);
  for(uint32 i = 0; i < 4; i++) {
    EXPECT_EQ(bd[i], newBitDepth[i]);
  }
}

TEST(YCoCgPixel, Conversion) {

  FasTC::Pixel p;
  p.R() = 127;
  p.G() = 127;
  p.B() = 127;
  p.A() = 255;

  FasTC::YCoCgPixel yp (p);
  EXPECT_EQ(yp.Y(), 127);
  EXPECT_EQ(yp.Co(), 128);
  EXPECT_EQ(yp.Cg(), 128);
}

TEST(YCoCgPixel, ConvertBack) {
  FasTC::Pixel p;

  p.R() = 241;
  p.G() = 22;
  p.B() = 102;
  p.A() = 124;

  FasTC::YCoCgPixel yp (p);
  FasTC::Pixel bp = yp.ToRGBA();

  for(int i = 0; i < 4; i++) {
    EXPECT_NEAR(p[i], bp[i], 1);
  }
}
