/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-10 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_RECTANGLEPLACEMENT_JUCEHEADER__
#define __JUCE_RECTANGLEPLACEMENT_JUCEHEADER__

#include "../geometry/juce_AffineTransform.h"
#include "../geometry/juce_Rectangle.h"


//==============================================================================
/**
    Defines the method used to postion some kind of rectangular object within
    a rectangular viewport.

    Although similar to Justification, this is more specific, and has some extra
    options.
*/
class JUCE_API  RectanglePlacement
{
public:
    //==============================================================================
    /** Creates a RectanglePlacement object using a combination of flags. */
    inline RectanglePlacement (int flags_) throw()  : flags (flags_) {}

    /** Creates a copy of another RectanglePlacement object. */
    RectanglePlacement (const RectanglePlacement& other) throw();

    /** Copies another RectanglePlacement object. */
    RectanglePlacement& operator= (const RectanglePlacement& other) throw();

    //==============================================================================
    /** Flag values that can be combined and used in the constructor. */
    enum
    {
        //==============================================================================
        /** Indicates that the source rectangle's left edge should be aligned with the left edge of the target rectangle. */
        xLeft                                   = 1,

        /** Indicates that the source rectangle's right edge should be aligned with the right edge of the target rectangle. */
        xRight                                  = 2,

        /** Indicates that the source should be placed in the centre between the left and right
            sides of the available space. */
        xMid                                    = 4,

        //==============================================================================
        /** Indicates that the source's top edge should be aligned with the top edge of the
            destination rectangle. */
        yTop                                    = 8,

        /** Indicates that the source's bottom edge should be aligned with the bottom edge of the
            destination rectangle. */
        yBottom                                 = 16,

        /** Indicates that the source should be placed in the centre between the top and bottom
            sides of the available space. */
        yMid                                    = 32,

        //==============================================================================
        /** If this flag is set, then the source rectangle will be resized to completely fill
            the destination rectangle, and all other flags are ignored.
        */
        stretchToFit                            = 64,

        //==============================================================================
        /** If this flag is set, then the source rectangle will be resized so that it is the
            minimum size to completely fill the destination rectangle, without changing its
            aspect ratio. This means that some of the source rectangle may fall outside
            the destination.

            If this flag is not set, the source will be given the maximum size at which none
            of it falls outside the destination rectangle.
        */
        fillDestination                         = 128,

        /** Indicates that the source rectangle can be reduced in size if required, but should
            never be made larger than its original size.
        */
        onlyReduceInSize                        = 256,

        /** Indicates that the source rectangle can be enlarged if required, but should
            never be made smaller than its original size.
        */
        onlyIncreaseInSize                      = 512,

        /** Indicates that the source rectangle's size should be left unchanged.
        */
        doNotResize                             = (onlyIncreaseInSize | onlyReduceInSize),

        //==============================================================================
        /** A shorthand value that is equivalent to (xMid | yMid). */
        centred                                 = 4 + 32
    };

    //==============================================================================
    /** Returns the raw flags that are set for this object. */
    inline int getFlags() const throw()                             { return flags; }

    /** Tests a set of flags for this object.

        @returns true if any of the flags passed in are set on this object.
    */
    inline bool testFlags (int flagsToTest) const throw()           { return (flags & flagsToTest) != 0; }


    //==============================================================================
    /** Adjusts the position and size of a rectangle to fit it into a space.

        The source rectangle co-ordinates will be adjusted so that they fit into
        the destination rectangle based on this object's flags.
    */
    void applyTo (double& sourceX,
                  double& sourceY,
                  double& sourceW,
                  double& sourceH,
                  double destinationX,
                  double destinationY,
                  double destinationW,
                  double destinationH) const throw();

    /** Returns the transform that should be applied to these source co-ordinates to fit them
        into the destination rectangle using the current flags.
    */
    template <typename ValueType>
    const Rectangle<ValueType> appliedTo (const Rectangle<ValueType>& source,
                                          const Rectangle<ValueType>& destination) const throw()
    {
        double x = source.getX(), y = source.getY(), w = source.getWidth(), h = source.getHeight();
        applyTo (x, y, w, h, static_cast <double> (destination.getX()), static_cast <double> (destination.getY()),
                 static_cast <double> (destination.getWidth()), static_cast <double> (destination.getHeight()));
        return Rectangle<ValueType> (static_cast <ValueType> (x), static_cast <ValueType> (y),
                                     static_cast <ValueType> (w), static_cast <ValueType> (h));
    }

    /** Returns the transform that should be applied to these source co-ordinates to fit them
        into the destination rectangle using the current flags.
    */
    const AffineTransform getTransformToFit (const Rectangle<float>& source,
                                             const Rectangle<float>& destination) const throw();


private:
    //==============================================================================
    int flags;
};

#endif   // __JUCE_RECTANGLEPLACEMENT_JUCEHEADER__
