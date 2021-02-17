

extern "C" {
void        initExternalModule();
const char* getModuleName();
const char* getModuleVersion();
const char* getModuleLicense();
const char* getModuleDescription();
const char* getModuleComponentList();
}

void initExternalModule() {}

const char* getModuleName() {
    return "SofaAwesome";
}

const char* getModuleVersion() {
    return "20.12";
}

const char* getModuleLicense() {
    return "LGPL";
}

const char* getModuleDescription() {
    return "Awesome plugin that brings many useful components.";
}

const char* getModuleComponentList() {
    return "";
}