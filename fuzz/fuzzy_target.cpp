#include <stdint.h>
#include <stddef.h>
#include "../CJsonObject.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    // Convert input data to a string
    std::string json_input(reinterpret_cast<const char*>(data), size);
    
    // Create a CJsonObject instance
    neb::CJsonObject oJson;
    
    // Attempt to parse the input
    if (oJson.Parse(json_input)) {
        // If parsing succeeds, perform operations on the JSON object
        oJson.ToString();
        oJson.ToFormattedString();
        
        // Traverse keys
        std::string key;
        while (oJson.GetKey(key)) {
            oJson.KeyExist(key);
        }

        // Attempt various JSON manipulations
        int intValue;
        double floatValue;
        std::string strValue;
        
        oJson.Get("timeout", floatValue);
        oJson.Get("some_integer", intValue);
        oJson.Get("some_string", strValue);
        
        oJson.Add("new_key", "new_value");
        oJson.Replace("timeout", 30.0);
        oJson.Delete("new_key");
        
        // Handle array values
        if (oJson.IsArray()) {
            for (int i = 0; i < oJson.GetArraySize(); ++i) {
                oJson(i);
            }
        }
    }
    
    return 0;
}
