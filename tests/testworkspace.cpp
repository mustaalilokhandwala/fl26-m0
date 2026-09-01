#include <cassert>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <stdexcept>

#include "Prompt.hpp"
#include "Workspace.hpp"
#include "Document.hpp"
#include "Message.hpp"

void construction_test() {
    Document d;
    assert(d.title().empty());
    assert(d.sourcePath().empty());
    assert(d.empty());

    Prompt p;
    assert(p.title().empty());
    assert(p.text().empty());
    assert(p.empty());

    Message m;
    assert(m.role() == MessageRole::User);
    assert(m.text().empty());
    assert(m.empty());

    Workspace w;
    assert(w.name().empty());
    assert(w.documentCount() == 0);
    assert(w.promptCount() == 0);
    assert(w.messageCount() == 0);
}

void equality_test() {
    Document d1("Notes", "Hello");
    Document d2("Notes", "Hello");

    assert(d1 == d2);

    d2.setTitle("Different");
    assert(d1 != d2);

    Prompt p1("Reviewer", "Review this.");
    Prompt p2("Reviewer", "Review this.");

    assert(p1 == p2);

    p2.setText("Different text");
    assert(p1 != p2);

    Message m1(MessageRole::User, "Hello");
    Message m2(MessageRole::User, "Hello");

    assert(m1 == m2);

    m2.setRole(MessageRole::Assistant);
    assert(m1 != m2);
}

void document_load_test() {
    const std::string path = "m0_test_document.txt";

    {
        std::ofstream output(path);
        output << "Test contents";
    }

    Document d("Old title", "Old contents");

    assert(d.load(path));
    assert(d.title() == "m0_test_document.txt");
    assert(d.sourcePath() == path);
    assert(d.contents() == "Test contents");
    assert(d.characterCount() == 13);

    Document beforeFailure = d;

    assert(!d.load("file_that_does_not_exist.txt"));
    assert(d == beforeFailure);

    std::remove(path.c_str());
}

void workspace_test() {
    Workspace w("Demo");

    w.addDocument(Document("Doc", "Text"));
    w.addPrompt(Prompt("Reviewer", "Review this requirement."));
    w.addMessage(Message(MessageRole::User, "Hello"));

    assert(w.documentCount() == 1);
    assert(w.promptCount() == 1);
    assert(w.messageCount() == 1);

    assert(w.documentAt(0).title() == "Doc");
    assert(w.promptAt(0).title() == "Reviewer");
    assert(w.messageAt(0).text() == "Hello");

    w.documentAt(0).setTitle("Changed");
    assert(w.documentAt(0).title() == "Changed");

    const Workspace& constWorkspace = w;

    assert(constWorkspace.documentAt(0).title() == "Changed");
    assert(constWorkspace.promptAt(0).title() == "Reviewer");
    assert(constWorkspace.messageAt(0).text() == "Hello");

    bool threw = false;

    try {
        w.documentAt(1);
    } catch (const std::out_of_range&) {
        threw = true;
    }

    assert(threw);
}

void copy_independence_test() {
    Workspace original("Original");
    original.addDocument(Document("Doc", "Text"));

    Workspace copy = original;

    assert(copy == original);

    original.setName("Changed");
    original.documentAt(0).setTitle("Changed Doc");

    assert(copy.name() == "Original");
    assert(copy.documentAt(0).title() == "Doc");
    assert(copy != original);
}

int main() {
    construction_test();
    equality_test();
    document_load_test();
    workspace_test();
    copy_independence_test();

    std::cout << "M0 tests passed\n";
    return 0;
}
