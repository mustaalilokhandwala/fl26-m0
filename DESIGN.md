# M0 Design and Understanding Note

Answer briefly in your own words. This is not intended to be a long report.

1. What responsibility belongs to `Workspace`, and what responsibilities belong to `Document`, `Prompt`, and `Message` instead?

Workspace represents the overall work context and stores the documents, prompts, and messages. Document stores document
information and loads text from a file. Prompt stores a title and reusable instruction text, while Message stores a role and 
message text.

2. Why are the collections inside `Workspace` private? Explain the purpose of the const and non-const `At` overloads.

The collections are private so they are accessed through the Workspace methods instead of being changed directly. The non-const
At methods allow a stored object to be changed, while the const versions provide read-only access.

3. Explain one meaningful test you added. What behavior does it check, and what implementation error could it catch?

I added a test that loads a valid file and then tries to load a file that does not exist. It checks that the failed load returns
false and that the existing document stays unchanged. This could catch an implementation that changes the document before
confirming that the new file loaded successfully.

4. Describe one implementation decision that you verified, tested, or revised before submitting your work.

I used at() in the Workspace access methods because the specification says an invalid index must throw std::out_of_range. I
added an invalid-index test to make sure this behavior worked correctly.

5. If generative AI was used, disclose it as required by course policy. If no generative AI was used, state that. The disclosure itself is not used as proof of authorship or understanding.

No generative AI was used.
