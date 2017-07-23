#ifndef __ParticleEmitterCommands_H__
#define __ParticleEmitterCommands_H__

#include "utils/include/prerequisites.h"
#include "base/StringInterface.h"

        /// Command object for ParticleEmitter  - see ParamCommand 
        class  CmdAngle : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdColour : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /// Command object for particle emitter  - see ParamCommand 
        class  CmdColourRangeStart : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdColourRangeEnd : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /// Command object for particle emitter  - see ParamCommand 
        class  CmdDirection : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /// Command object for particle emitter  - see ParamCommand 
        class  CmdEmissionRate : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdVelocity : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdMinVelocity : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdMaxVelocity : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdTTL : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdMinTTL : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdMaxTTL : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdPosition : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdDuration : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdMinDuration : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdMaxDuration : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdRepeatDelay : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdMinRepeatDelay : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for particle emitter  - see ParamCommand 
        class  CmdMaxRepeatDelay : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
		/// Command object for particle emitter  - see ParamCommand
        class  CmdName : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

		/// Command object for particle emitter  - see ParamCommand 
        class  CmdEmittedEmitter : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

		/// Command object for particle emitter  - see ParamCommand
        class  CmdTexCoordIndex : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

		/// Command object for particle emitter  - see ParamCommand
        class  CmdMaxWidth : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

		/// Command object for particle emitter  - see ParamCommand
        class  CmdMaxHeight : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

		/// Command object for particle emitter  - see ParamCommand
        class  CmdMaxSizeFixed : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

		/// Command object for particle emitter  - see ParamCommand
        class  CmdMaxSizeFactor : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /// Command object for particle emitter  - see ParamCommand
        class  CmdPositionFactor : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /// Command object for particle emitter  - see ParamCommand
        class  CmdPositionXFactor : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /// Command object for particle emitter  - see ParamCommand
        class  CmdPositionYFactor : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

		/// Command object for particle emitter  - see ParamCommand
        class  CmdMinTexCoordIndex : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

		/// Command object for particle emitter  - see ParamCommand
        class  CmdMaxTexCoordIndex : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class  CmdEnableAngleDirecitonSync : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
#endif

