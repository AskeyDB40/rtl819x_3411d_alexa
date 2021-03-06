/*
 * Copyright (C) 2012 Nokia Corporation.
 *
 * Author: Jens Georg <jensg@openismus.com>
 *
 * This file is part of Rygel.
 *
 * Rygel is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Rygel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

[CCode (cname = "uuid_generate", cheader_filename = "uuid/uuid.h")]
internal extern static void uuid_generate ([CCode (array_length = false)]
                                           uchar[] uuid);
[CCode (cname = "uuid_unparse", cheader_filename = "uuid/uuid.h")]
internal extern static void uuid_unparse ([CCode (array_length = false)]
                                          uchar[] uuid,
                                          [CCode (array_length = false)]
                                          uchar[] output);

public const string DIDL_ITEM = """<?xml version="1.0" encoding="UTF-8"?>
<DIDL-Lite
    xmlns:dc="http://purl.org/dc/elements/1.1/"
    xmlns="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/"
    xmlns:upnp="urn:schemas-upnp-org:metadata-1-0/upnp/"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:schemaLocation="urn:schemas-upnp-org:metadata-1-0/DIDL-Lite/
        http://www.upnp.org/schemas/av/didl-lite-v2-20060531.xsd
      urn:schemas-upnp-org:metadata-1-0/upnp/
        http://www.upnp.org/schemas/av/upnp-v2-20060531.xsd">
    <item id="" parentID="0" restricted="0">
        <dc:title>New Song</dc:title>
        <upnp:class>object.item.audioItem</upnp:class>
        <res protocolInfo="*:*:*:*" />
    </item>
</DIDL-Lite>""";

public class Rygel.ServiceAction : GLib.Object {
    public int error_code;
    public string error_message;
    public string id;
    public string elements;

    public ServiceAction (string? container_id,
                          string? elements) {
        this.id = container_id;
        this.elements = elements;
    }

    public void @return() {}
    public void return_error (int code, string message) {
        this.error_code = code;
        this.error_message = message;
    }

    public new void @get (string arg1_name,
                          Type arg1_type,
                          out string arg1_val,
                          string arg2_name,
                          Type arg2_type,
                          out string arg2_val) {
        assert (arg1_name == "ContainerID");
        assert (arg1_type == typeof (string));
        arg1_val = id;

        assert (arg2_name == "Elements");
        assert (arg2_type == typeof (string));
        arg2_val = elements;
    }

    public new void @set (string arg1_name,
                          Type arg1_type,
                          string arg1_val,
                          string arg2_name,
                          Type arg2_type,
                          string arg2_val) {
        assert (arg1_name == "ObjectID");
        assert (arg1_type == typeof (string));

        assert (arg2_name == "Result");
        assert (arg2_type == typeof (string));
    }
}

public class Rygel.HTTPServer : GLib.Object {
}

public class Rygel.ItemRemovalQueue : GLib.Object {
    public static ItemRemovalQueue get_default () {
        return new ItemRemovalQueue ();
    }

    public void queue (MediaItem item, Cancellable? cancellable) {
    }
}

public class Rygel.MediaObject : GLib.Object {
    public string id;
    public string ref_id;
    public unowned MediaContainer parent;
    public string upnp_class;
    public string title;
    public GUPnP.OCMFlags ocm_flags;
    public Gee.ArrayList<string> uris;

    public void add_uri (string uri) {
        this.uris.add (uri);
    }
}

public class Rygel.MediaItem : Rygel.MediaObject {
    public string dlna_profile;
    public string mime_type;
    public long size;
    public bool place_holder;
    public string date;

    public MediaItem (string id, MediaContainer parent, string title) {
        this.id = id;
        this.parent = parent;
        this.title = title;
    }

    public void serialize (GUPnP.DIDLLiteWriter writer, HTTPServer server) {
    }
}

public class Rygel.MusicItem : Rygel.AudioItem {
    public const string UPNP_CLASS = "object.item.audioItem.musicTrack";

    public MusicItem (string id, MediaContainer parent, string title) {
        base (id, parent, title);
    }
}

public class Rygel.AudioItem : Rygel.MediaItem {
    public const string UPNP_CLASS = "object.item.audioItem";
    public string artist;
    public string album;

    public AudioItem (string id, MediaContainer parent, string title) {
        base (id, parent, title);
    }
}
public class Rygel.ImageItem : Rygel.MediaItem {
    public const string UPNP_CLASS = "object.item.imageItem";
    public ImageItem (string id, MediaContainer parent, string title) {
        base (id, parent, title);
    }
}

public class Rygel.VideoItem : Rygel.MediaItem {
    public const string UPNP_CLASS = "object.item.videoItem";
    public VideoItem (string id, MediaContainer parent, string title) {
        base (id, parent, title);
    }
}

public class Rygel.PhotoItem : Rygel.MediaItem {
    public const string UPNP_CLASS = "object.item.imageItem.photo";
    public string creator;

    public PhotoItem (string id, MediaContainer parent, string title) {
        base (id, parent, title);
    }
}
public class Rygel.ContentDirectory : GLib.Object {
    public Cancellable cancellable;
    public MediaContainer root_container;
    public HTTPServer http_server;
}

public class Rygel.MediaContainer : Rygel.MediaObject {
    public Gee.ArrayList<string> create_classes = new Gee.ArrayList<string> ();
    public int child_count;
    public string sort_criteria = "+dc:title";

    // mockable elements
    public MediaObject found_object = null;

    public async MediaObject? find_object (string       id,
                                           Cancellable? cancellable = null) {
        Idle.add (() => { find_object.callback (); return false; });
        yield;

        return found_object;
    }

    public signal void container_updated (MediaContainer container);
}

public class Rygel.MediaObjects : Gee.ArrayList<MediaObject> {
}

public class Rygel.WritableContainer : Rygel.MediaContainer {
    public bool can_create (string upnp_class) {
        return this.create_classes.contains (upnp_class);
    }

    public async File? get_writable (Cancellable? cancellable = null) {
        return File.new_for_commandline_arg ("/tmp");
    }

    public async void add_item (MediaItem    item,
                                Cancellable? cancellable = null) {
    }
}

public class Rygel.SearchableContainer : Rygel.MediaContainer {
    public MediaObjects result = new MediaObjects ();

    public async MediaObjects search (SearchExpression expression,
                                      int              offset,
                                      int              count,
                                      out int          total_matches,
                                      string           soer_criteria,
                                      Cancellable?     cancellable = null) {
        Idle.add (() => { search.callback (); return false; });
        yield;

        return result;
    }
}

public errordomain Rygel.ContentDirectoryError {
    BAD_METADATA,
    NO_SUCH_OBJECT,
    INVALID_ARGS,
    RESTRICTED_PARENT,
    ERROR
}

public class Rygel.HTTPItemCreatorTest : GLib.Object {

    public static int main (string[] args) {
        var test = new HTTPItemCreatorTest ();
        test.test_parse_args ();
        test.test_didl_parsing ();
        test.test_fetch_container ();

        return 0;
    }

    // expected errors
    Error no_such_object;
    Error restricted_parent;
    Error bad_metadata;
    Error invalid_args;

    public HTTPItemCreatorTest () {
        this.no_such_object = new ContentDirectoryError.NO_SUCH_OBJECT("");
        this.restricted_parent = new ContentDirectoryError.RESTRICTED_PARENT("");
        this.bad_metadata = new ContentDirectoryError.BAD_METADATA("");
        this.invalid_args = new ContentDirectoryError.INVALID_ARGS("");
    }

    private void test_parse_args () {
        // check null container id
        var content_directory = new ContentDirectory ();

        var action = new ServiceAction (null, "");
        var creator = new ItemCreator (content_directory, action);
        creator.run ();
        assert (action.error_code == no_such_object.code);

        // check elements containing a comment
        action = new ServiceAction ("0", "<!-- This is an XML comment -->");
        creator = new ItemCreator (content_directory, action);
        creator.run ();
        assert (action.error_code == bad_metadata.code);

        // check null elements
        action = new ServiceAction ("0", null);
        creator = new ItemCreator (content_directory, action);
        creator.run ();
        assert (action.error_code == bad_metadata.code);
    }

    private void test_didl_parsing_step (Xml.Doc *doc, int expected_code) {
        string xml;

        doc->dump_memory_enc (out xml);
        var action = new ServiceAction ("0", xml);
        var content_directory = new ContentDirectory ();
        var creator = new ItemCreator (content_directory, action);
        creator.run ();
        assert (action.error_code == expected_code);
    }

    private void test_didl_parsing () {
        var xml = Xml.Parser.read_memory (DIDL_ITEM,
                                          DIDL_ITEM.length,
                                          null,
                                          null,
                                          Xml.ParserOption.RECOVER |
                                          Xml.ParserOption.NOBLANKS);
        var didl_node = xml->children;
        var item_node = didl_node->children;
        var content_directory = new ContentDirectory ();

        // test no DIDL
        var action = new ServiceAction ("0", "");
        var creator = new ItemCreator (content_directory, action);
        creator.run ();
        assert (action.error_code == bad_metadata.code);
        assert (action.error_message == "Bad metadata");

        // test empty DIDL
        item_node->unlink ();
        didl_node->set_content ("  ");
        this.test_didl_parsing_step (xml, bad_metadata.code);

        // test item node with missing restricted attribute
        var tmp = item_node->copy (1);
        tmp->unset_prop ("restricted");
        didl_node->add_child (tmp);
        this.test_didl_parsing_step (xml, bad_metadata.code);

        // test item node with restricted=1
        tmp->set_prop ("restricted", "1");
        this.test_didl_parsing_step (xml, invalid_args.code);

        // test item node with invalid id
        tmp->unlink ();
        tmp = item_node->copy (1);
        tmp->set_prop ("id", "InvalidItemId");
        didl_node->add_child (tmp);
        this.test_didl_parsing_step (xml, bad_metadata.code);

        // test item node with missing id
        tmp->unset_prop ("id");
        this.test_didl_parsing_step (xml, bad_metadata.code);

        // test item node with missing title
        tmp->unlink ();
        tmp = item_node->copy (1);
        var title_node = tmp->children;
        title_node->unlink ();
        didl_node->add_child (tmp);
        this.test_didl_parsing_step (xml, bad_metadata.code);

        // test missing, empty or non-item upnp class
        tmp->unlink ();
        tmp = item_node->copy (1);
        var class_node = tmp->children->next;
        class_node->set_content ("object.container");
        didl_node->add_child (tmp);
        this.test_didl_parsing_step (xml, bad_metadata.code);

        class_node->set_content ("");
        this.test_didl_parsing_step (xml, bad_metadata.code);

        class_node->unlink ();
        this.test_didl_parsing_step (xml, bad_metadata.code);
    }

    private void test_fetch_container_run (ItemCreator creator) {
        var main_loop = new MainLoop (null, false);
        creator.run.begin ( () => { main_loop.quit (); });
        main_loop.run ();
    }

    private void test_fetch_container () {
        // check case when object is not found
        var content_directory = new ContentDirectory ();
        var root_container = new SearchableContainer ();
        content_directory.root_container = root_container;
        var action = new ServiceAction ("0", DIDL_ITEM);
        var creator = new ItemCreator (content_directory, action);
        this.test_fetch_container_run (creator);
        assert (action.error_code == no_such_object.code);

        // check case when found object is not a container → Error 710
        // cf. ContentDirectory:2 spec, Table 2-22
        root_container.found_object = new MediaObject ();
        this.test_fetch_container_run (creator);
        assert (action.error_code == no_such_object.code);

        // check case when found container does not have OCMUpload set
        root_container.found_object = new MediaContainer ();
        this.test_fetch_container_run (creator);
        assert (action.error_code == restricted_parent.code);

        // check case when found container is not a writable container
        root_container.found_object.ocm_flags |= GUPnP.OCMFlags.UPLOAD;
        this.test_fetch_container_run (creator);
        assert (action.error_code == restricted_parent.code);

        // check when found container does not have the correct create class
        var container = new WritableContainer ();
        container.create_classes.add ("object.item.imageItem.musicTrack");
        container.ocm_flags |= GUPnP.OCMFlags.UPLOAD;
        root_container.found_object = container;
        this.test_fetch_container_run (creator);
        assert (action.error_code == bad_metadata.code);

        // check DLNA.ORG_AnyContainer when root container is not searchable
        content_directory.root_container = new MediaContainer ();
        action.id = "DLNA.ORG_AnyContainer";
        this.test_fetch_container_run (creator);
        assert (action.error_code == no_such_object.code);

        // check DLNA.ORG_AnyContainer when no writable container is found
        content_directory.root_container = new SearchableContainer ();
        this.test_fetch_container_run (creator);
        // We cannot distinguish this case from the "create-class doesn't match"
        // case
        assert (action.error_code == bad_metadata.code);
    }
}
