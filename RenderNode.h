#include "enum_flags.h"

namespace Approach
{
    namespace Renderable
    {
        ENUM_FLAGS(RenderFlags)
        enum class RenderFlags //: uint32_t
        {
            none                = 0x00,
            OpenRendered        = 0x1,
            ContentRendered     = 0x2,
            ContentOnly         = 0x4,
            EnsureChildren      = 0x8,
            Listening           = 0x100,
            PerforationPoint    = 0x200
        };

        template <class OutStream>
        class RenderNode
        {
            public:

            virtual void render(OutStream& OutputStream)=0;

            /** Outputs this node's header any initial data */
            virtual void RenderHead(OutStream& OutputStream)=0;
            /** Outputs any child nodes to stream. */
            virtual void RenderCorpus(OutStream& OutputStream)=0;
            /** Outputs closing data */
            virtual void RenderTail(OutStream& OutputStream)=0;

            /** Nests child nodes into the instance by pointer */
            virtual void operator<<(RenderNode* incoming)=0;
            /** Nests child nodes into the instance by reference */
            virtual void operator<<(RenderNode &incoming)=0;
        };
    }
}
