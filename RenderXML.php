<?php

/*
	Title: Renderale Class for Approach


	Copyright 2002-2016 Garet Claborn

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

*/

class RenderXML
{
	public static $renderObjectIndex=0;
	public static $NoAutoRender=array('html', 'head', 'body', 'script', 'style', 'channel', 'rss', 'item','title');
	
	public $id=null;
	public $pageID='';

	public $tag='div';
	public $classes=Array();
	public $attributes=Array();
	public $content=null;
	public $children=Array();

	public $prefix='';
	public $infix='';
	public $postfix='';
	
	public $selfContained=false;

	function RenderXML($t='div', $pageID='', $options=array())
	{
		$this->id=renderable::$renderObjectIndex;
		renderable::$renderObjectIndex++;				/*	Register New Renderable	*/

		if( is_array($t) ){ $options = array_merge($t,$options); $this->tag= isset($options['tag']) ? $options['tag'] : 'div';}
		else $this->tag = $t;
	
	
		if( is_array($pageID) ){ $options = array_merge($pageID,$options); $this->pageID= isset($options['pageID']) ? $options['pageID'] : get_class($this) . $this->id;}
		else $this->pageID = $pageID;	
			
		if(isset($options['pageID']) )	$this->pageID = $options['pageID'];
		if(isset($options['template'])) $this->content = GetFile($options['template']);
		if(isset($options['classes']) ) $this->classes = $options['classes'];
		if(isset($options['attributes'])) $this->attributes = $options['attributes'];
		if(isset($options['selfcontained'])) $this->selfContained = $options['selfcontained'];
		if(isset($options['content'])) $this->content = $options['content'] . $this->content;
		if(in_array($this->tag,renderable::$NoAutoRender)) $this->pageID='';
	}

	public function buildClasses()
	{
		$classesToString='';
		if(is_array($this->classes) && count($this->classes) >0 )
		{
			foreach($this->classes as $style)
			{
				$classesToString .= $style . ' ';
			}
			return $this->classes=' class="'.trim($classesToString).'" ';
		}
		elseif(is_string($this->classes) && $this->classes != '')
		{
			return $this->classes = ' class="'.trim($this->classes).'" ';
		}
		elseif(in_array($this->tag,renderable::$NoAutoRender)){ return ''; }
		else
		{
			return ' class="'.get_class($this) .' '. get_class($this) .'_'.$this->id . '" ';
		}
	}
	public function buildContent()
	{
		foreach($this->children as $renderObject)
		{
			$this->content .= $renderObject->render();
		}
	}

	public function buildAttributes()
	{
		$attribsToString=' ';
		if(is_array($this->attributes) )
		{
			foreach($this->attributes as $att=>$val)
			{
				if(is_array($val) )
				{
					foreach($val as $_att=>$_val)
					{
						$attribsToString .= $_att . '="'.$_val.'" ';
					}
					return $this->attributes=$attribsToString;
				}
				else $attribsToString .= $att . '="'.$val.'" ';
			}
			return $this->attributes=$attribsToString;
		}
		else if(is_string($this->attributes))	return ' '.$this->attributes.' ';	
		else	$attribsToString = ' data-approach-error="ATTRIBUTE_RENDER_ERROR" ';
		
		return $this->attributes=$attribsToString;
	}

	public function render()
	{
		$OutputStream='';
		$this->buildContent();
 
		$OutputStream = $this->prefix . 
			'<' . $this->tag .
			( $this->pageID != ''		?	' id="'.$this->pageID.'" '	: '')	.
			( isset($this->attributes)	?	$this->buildAttributes()	: '')	.
			( isset($this->classes)		?	$this->buildClasses()		: '')	.
			($this->selfContained 		?	'/>'.PHP_EOL				: '>'	.
			$FrontendMarkup . $this->content . $this->infix. '</' . $this->tag . '>' . PHP_EOL) .
			$this->postfix;

		return $OutputStream;
	}
}


?>