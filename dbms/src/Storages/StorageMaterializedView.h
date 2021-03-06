#pragma once

#include <ext/shared_ptr_helper.h>

#include <Storages/StorageView.h>


namespace DB
{

class StorageMaterializedView : public ext::shared_ptr_helper<StorageMaterializedView>, public StorageView
{
friend class ext::shared_ptr_helper<StorageMaterializedView>;

public:
    static StoragePtr create(
        const String & table_name_,
        const String & database_name_,
        Context & context_,
        ASTPtr & query_,
        NamesAndTypesListPtr columns_,
        const NamesAndTypesList & materialized_columns_,
        const NamesAndTypesList & alias_columns_,
        const ColumnDefaults & column_defaults_,
        bool attach_);

    std::string getName() const override { return "MaterializedView"; }
    std::string getInnerTableName() const { return  ".inner." + table_name; }
    StoragePtr getInnerTable() const;

    NameAndTypePair getColumn(const String & column_name) const override;
    bool hasColumn(const String & column_name) const override;

    bool supportsSampling() const override             { return getInnerTable()->supportsSampling(); }
    bool supportsPrewhere() const override             { return getInnerTable()->supportsPrewhere(); }
    bool supportsFinal() const override             { return getInnerTable()->supportsFinal(); }
    bool supportsParallelReplicas() const override     { return getInnerTable()->supportsParallelReplicas(); }
    bool supportsIndexForIn() const override         { return getInnerTable()->supportsIndexForIn(); }

    BlockOutputStreamPtr write(const ASTPtr & query, const Settings & settings) override;
    void drop() override;
    bool optimize(const ASTPtr & query, const String & partition, bool final, bool deduplicate, const Settings & settings) override;

    BlockInputStreams read(
        const Names & column_names,
        const ASTPtr & query,
        const Context & context,
        QueryProcessingStage::Enum & processed_stage,
        size_t max_block_size,
        unsigned num_streams) override;

private:
    StorageMaterializedView(
        const String & table_name_,
        const String & database_name_,
        Context & context_,
        ASTPtr & query_,
        NamesAndTypesListPtr columns_,
        const NamesAndTypesList & materialized_columns_,
        const NamesAndTypesList & alias_columns_,
        const ColumnDefaults & column_defaults_,
        bool attach_);
};

}
