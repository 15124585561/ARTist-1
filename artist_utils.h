/**
 * The ARTist Project (https://artist.cispa.saarland)
 *
 * Copyright (C) 2017 CISPA (https://cispa.saarland), Saarland University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @author "Oliver Schranz <oliver.schranz@cispa.saarland>"
 * @author "Sebastian Weisgerber <weisgerber@cispa.saarland>"
 *
 */

#ifndef ART_ARTIST_UTILS_H_
#define ART_ARTIST_UTILS_H_

#include <optimizing/nodes.h>

#include "optimizing/artist/env/codelib_environment.h"
#include "artist_typedefs.h"
#include "env/codelib_symbols.h"
#include "injection/injection.h"

using std::runtime_error;
using std::shared_ptr;

class HGraph;
class HInstruction;


namespace art {

  class CompilerDriver;
  class DexCompilationUnit;
  class Injection;
  class CodeLibEnvironment;

  class ArtUtils {
   public:
    static string GetDexName(const string& dex_name, uint32_t dex_file_idx);

   public:
    static const DexFile::MethodId* FindMethodId(const HGraph* graph, const string& searched_method_name);
    static const DexFile::MethodId* FindMethodId(const DexFile& dex_file, const string& searched_method_name);

    static MethodIdx FindMethodIdx(const HGraph* graph, const string& searched_method_name);
    static MethodIdx FindMethodIdx(const DexFile& dex_file, const string& searched_method_name);

    static TypeIdx FindTypeIdxFromName(const HGraph* graph, const string & searched_type_name);
    static TypeIdx FindTypeIdxFromName(const DexFile& dex_file, const string & searched_type_name);

    static FieldIdx FindFieldIdxFromName(const HGraph* graph, const string & searched_field_name);
    static FieldIdx FindFieldIdxFromName(const DexFile& dex_file, const string & searched_field_type);

    static ClassDefIdx FindClassDefIdxFromName(const HGraph* graph, const  string & searched_class_name);
    static ClassDefIdx FindClassDefIdxFromName(const DexFile& dex_file, const  string & searched_class_name);

    static void DumpTypes(const HGraph* graph);
    static void DumpTypes(const DexFile& dex_file);

    static string GetMethodName(HInvoke* invoke, bool signature = false);
    static string GetMethodSignature(const HInvoke* invoke);

        static string GetDexFileName(const HGraph* graph);

    static void DumpFields(const HGraph* graph);
    static void DumpFields(const DexFile& dex_file);

    static HInstruction* InjectCodeLib(const HInstruction* instruction_cursor,
                                       shared_ptr<CodeLibEnvironment> env,
                                       const bool entry_block_injection = true);
    static HInstruction* InjectMethodCall(HInstruction* instruction_cursor,
                                       const string& method_signature,
                                       vector<HInstruction*>& function_params,
                                          shared_ptr<CodeLibEnvironment> env,
                                       const Primitive::Type return_type = Primitive::Type::kPrimVoid,
                                       const bool inject_before = true);

    static void ExtractMethodArguments(const string &signature, vector<string> &result);
    static string ExtractMethodReturnValue(const string& method_signature);

    static uint32_t SetupInstructionArguments(HInvoke* instruction, vector<HInstruction*>& instruction_arguments);
    static void SetupFunctionParams(HGraph* graph,
                                    const Injection&,
                                    vector<HInstruction*>& function_parameters);

    static bool IsNativeMethod(HInvoke* instruction);

    static mirror::Class* GetClassFrom(CompilerDriver* driver, const DexCompilationUnit& compilation_unit);

#ifndef BUILD_MARSHMALLOW

    static void AppendInstruction(HInstruction* instruction, HInstruction* previous_instruction);
    static void InsertInstructionAtTop(HInstruction* instruction, HInstruction* previous_instruction);
    static void InitializeInstruction(HInstruction* instruction, HInstruction* previous_instruction);

#endif
  };

}  // namespace art

#endif  // ART_ARTIST_UTILS_H_

