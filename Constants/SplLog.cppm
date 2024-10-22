export module Constants:SplLog;

export namespace Constants {
    namespace SplLog {
        namespace Print {
            constexpr bool time       = true;
            constexpr bool log_level  = false;

            namespace source {
                constexpr bool location = false;
                constexpr bool file     = true;
                constexpr bool line     = true;
                constexpr bool col      = true;
                constexpr bool function = true;
            }
        }
    }
}