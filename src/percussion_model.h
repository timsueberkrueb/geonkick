/**
 * File name: percussion_model.h
 * Project: Geonkick (A percussion synthesizer)
 *
 * Copyright (C) 2020 Iurie Nistor <http://geontime.com>
 *
 * This file is part of Geonkick.
 *
 * GeonKick is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef PERCUSSION_MODEL_H
#define PERCUSSION_MODEL_H

#include "globals.h"

class GeonkickApi;
class GeonkickState;

class PercussionModel : public RkObject {
 public:
        using KeyIndex = int;
        explicit PercussionModel(GeonkickApi* api, int id);
        virtual ~PercussionModel();
        void setId(int id);
        int id(int id) const;
        void select();
        bool isSelected() const;
        void increasePercussionChannel();
        void decreasePercussionChannel();
        void setKey(KeyIndex keyIndex);
        KeyIndex key(KeyIndex keyIndex) const;
        void setName(const std::string &name);
        std::string name(PercussionIndex index) const;
        int channel(PercussionIndex index) const;
        bool canCopy() const;
        bool canRemove() const;
        void play();
        void setLimiter(int value);
        void mute(bool b);
        bool isMuted() const;
        void solo(bool b);
        bool isSolo() const;

        /* RK_DECL_ACT(modelUpdated, */
        /*             modelUpdated(), */
        /*             RK_ARG_TYPE(), */
        /*             RK_ARG_VAL()); */
        /* RK_DECL_ACT(levelerUpdated, */
        /*             levelerUpdated(PercussionIndex index, int val), */
        /*             RK_ARG_TYPE(PercussionIndex, int), */
        /*             RK_ARG_VAL(index, val)); */
        /* RK_DECL_ACT(limiterUpdated, */
        /*             limiterUpdated(PercussionIndex index), */
        /*             RK_ARG_TYPE(PercussionIndex), */
        /*             RK_ARG_VAL(index)); */
        /* RK_DECL_ACT(muteUpdated, */
        /*             muteUpdated(PercussionIndex index, bool b, */
        /*             RK_ARG_TYPE(PercussionIndex, bool), */
        /*             RK_ARG_VAL(index, b)); */
        /* RK_DECL_ACT(soloUpdated, */
        /*             soloUpdated(PercussionIndex index, bool b), */
        /*             RK_ARG_TYPE(PercussionIndex, bool), */
        /*             RK_ARG_VAL(index, b)); */

 /* protected: */
 /*        int getPercussionId(int index) const; */

 private:
        GeonkickApi *geonkickApi;
};

#endif // PERCUSSION_MODEL_H
