            <div style="width:100%;float:none;clear:both;"></div>

            <?php
            //If we're looking at a test result, include the inner test result div
            if( !strcasecmp('Test Result', $tab) && !$nosubheader )
            {
                echo '</div></div>';
            }
            ?>
            </div>
        </div>
    </div>
</div>

   
    <?php
        $feeds = null;
        if( is_file('./tmp/feeds.dat') )
            $feeds = json_decode(file_get_contents('./tmp/feeds.dat'), true);
        
        if( count($feeds) && !defined('BARE_UI') )
        {
            echo '<table id="feeds"><tr>';
            
            // display the column headers
            foreach( $feeds as $title => &$feed )
                echo "<th>$title</th>";
            echo '</tr><tr>';
            
            // display the feed contents
            $column = 0;
            foreach( $feeds as $title => &$feed )
            {
                $column++;
                echo '<td><ul>';
                
                // keep a list of titles so we only display the most recent (for threads)
                $titles = array();
                
                $count = 0;
                $extended = false;
                foreach( $feed as $time => &$item )
                {
                    if( $count <= 25 )
                    {
                        $dupe = false;
                        foreach( $titles as $title )
                            if( $title == $item['title'] )
                                $dupe = true;
                        
                        if( !$dupe )
                        {
                            $count++;
                            if( $count == 6 )
                            {
                                $extended = true;
                                echo "<li id=\"show_more_feeds_$column\"><a href=\"javascript:void(o)\" onclick=\"showFeeds($column)\">more...</a></li><li class=\"morefeeds\" ><div id=\"more_feeds_$column\" class=\"hidden\"><ul>";
                            }
                        
                            $titles[] = $item['title'];
                            echo "<li><a title=\"{$item['source']}\" href=\"{$item['link']}\">{$item['title']}</a></li>";
                        }
                    }
                }
                
                unset($titles);
                
                if( $extended )
                    echo '</ul></div></li>';
                    
                echo '</ul></td>';
            }
            echo '</tr></table>';
        }
    ?>

    <?php
        // display the sponsor logos across the bottom of the page
        $sponsors = array();
        $s = parse_ini_file('./settings/sponsors.ini', true);
        foreach( $s as &$entry )
            if( strlen($entry['logo']) ) {
                $offset = 0;
                if( $entry['index'] )
                    $offset = -40 * $entry['index'];
                $sponsors[] = array('logo' => $GLOBALS['cdnPath'] . $entry['logo'], 'href' => $entry['href'], 'title' => $entry['alt'], 'offset' => $offset);
            }
        
        $count = count($sponsors);
        if( $count && !defined('BARE_UI') )
        {
            echo '<div id="sponsor_header">WebPagetest Partners</div>';
            shuffle($sponsors);
            
            $rows = ceil((float)$count / 5.0);
            $rowCount = ceil((float)$count / (float)$rows);
            echo '<div id="links">';
            echo'<table class="links"><tr>';
            $i = 0;
            $remaining = $count;
            foreach( $sponsors as &$sponsor )
            {
                if( $i >= $rowCount || ($i == $rowCount - 1 && $remaining < 4 && $remaining > $rowCount) )
                {
                    $i = 1;
                    echo '</tr></table><table class="links"><tr>';
                }
                else
                    $i++;

                $remaining--;
                $style = "background-image: url({$sponsor['logo']}); background-position: 0px {$sponsor['offset']}px;";
                echo "<td ><a href=\"{$sponsor['href']}\" title=\"{$sponsor['alt']}\"><div class=\"sponsor_logo\" style=\"$style\"></div></a></td>";
                if( $remaining && $remaining < $rowCount - $i - 1 )
                    echo '<td></td>';
            }
            echo '</tr></table>';
            echo '</div>';
        }
    ?>
    <div class="cleared"></div>
    
    <script type="text/javascript">
        function showFeeds(column)
        {
            var label = document.getElementById("show_more_feeds_" + column);
            label.parentNode.removeChild( label );
            
            document.getElementById("more_feeds_" + column).className = "";
            return false;
        }
    </script>
    <script type="text/javascript" src="<?php echo $GLOBALS['cdnPath']; ?>/js/site.js?v=<?php echo VER_JS;?>"></script>
    <?php
    if(extension_loaded('newrelic'))
        echo @newrelic_get_browser_timing_footer();
    ?>
    