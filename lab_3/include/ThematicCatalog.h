#pragma once
#include "../include/Catalog.h"

class ThematicCatalog : public Catalog {
public:
    LibraryCard** search(const std::string& code, int& resultCount) override;
};