#ifndef __OverlayElementEmitterCommands_H__
#define __OverlayElementEmitterCommands_H__

#include "asset/OverlayPrerequisites.h"
#include "base/StringInterface.h"

//namespace E3D  {

	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Overlays
	*  @{
	*/

    namespace OverlayElementCommands {
        /// Command object for OverlayElement  - see ParamCommand 
        class CmdLeft : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for OverlayElement  - see ParamCommand 
        class CmdTop : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for OverlayElement  - see ParamCommand 
        class CmdWidth : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for OverlayElement  - see ParamCommand 
        class CmdHeight : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for OverlayElement  - see ParamCommand 
        class CmdMaterial : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for OverlayElement  - see ParamCommand 
        class CmdCaption : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for OverlayElement  - see ParamCommand 
        class CmdMetricsMode : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for OverlayElement  - see ParamCommand 
        class CmdHorizontalAlign : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for OverlayElement  - see ParamCommand 
        class CmdVerticalAlign : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /// Command object for OverlayElement  - see ParamCommand 
        class CmdVisible : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
    }
	/** @} */
	/** @} */
//}

#endif


