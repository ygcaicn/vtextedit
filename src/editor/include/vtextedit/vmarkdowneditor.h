#ifndef VTEXTEDIT_VMARKDOWNEDITOR_H
#define VTEXTEDIT_VMARKDOWNEDITOR_H

#include <vtextedit/vtexteditor.h>

namespace vte
{
    class PegMarkdownHighlighter;
    class EditorPegMarkdownHighlighter;
    class DocumentResourceMgr;
    class TextDocumentLayout;
    class EditorPreviewMgr;
    class PreviewMgr;
    class MarkdownEditorConfig;

    class VTEXTEDIT_EXPORT VMarkdownEditor : public VTextEditor
    {
        Q_OBJECT

        friend class EditorPreviewMgr;

    public:
        VMarkdownEditor(const QSharedPointer<MarkdownEditorConfig> &p_config,
                        QWidget *p_parent = nullptr);

        virtual ~VMarkdownEditor();

        void setSyntax(const QString &p_syntax) Q_DECL_OVERRIDE;
        QString getSyntax() const Q_DECL_OVERRIDE;

        DocumentResourceMgr *getDocumentResourceMgr() const;

        TextDocumentLayout *documentLayout() const;

        PegMarkdownHighlighter *getHighlighter() const;

        PreviewMgr *getPreviewMgr() const;

        void setConfig(const QSharedPointer<MarkdownEditorConfig> &p_config);

        void zoom(int p_delta) Q_DECL_OVERRIDE;

    protected:
        bool eventFilter(QObject *p_obj, QEvent *p_event) Q_DECL_OVERRIDE;

    private:
        void setupDocumentLayout();

        void setupSyntaxHighlighter();

        void setupPreviewMgr();

        void updateFromConfig();

        // Return true if @p_event is handled.
        bool handleKeyPressEvent(QKeyEvent *p_event);

        bool handleKeyReturn(QKeyEvent *p_event);

        // Managed by QObject.
        PegMarkdownHighlighter *m_highlighter = nullptr;

        QScopedPointer<EditorPegMarkdownHighlighter> m_highlighterInterface;

        QScopedPointer<DocumentResourceMgr> m_resourceMgr;

        QScopedPointer<EditorPreviewMgr> m_previewMgrInterface;

        // Managed by QObject.
        PreviewMgr *m_previewMgr = nullptr;

        QSharedPointer<MarkdownEditorConfig> m_config;
    };
}

#endif
